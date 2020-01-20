#include "pch.h"

#include "jni.h"
#include "keyboardListener.h"

static volatile bool hooking = false;
static bool block = false;
static HHOOK keyboardHook;

JNIEnv* envi;
jclass keyboardReceiverClass;

jmethodID m_keyPress, m_keyRelease, m_keyHotKey;

static bool isKeyPressed(int key) {
	return GetAsyncKeyState(key) & 0x8000;
}

static bool isShiftPressed() {
	return isKeyPressed(VK_LSHIFT) || isKeyPressed(VK_RSHIFT);
}

static bool isControlPressed() {
	return isKeyPressed(VK_LCONTROL) || isKeyPressed(VK_RCONTROL);
}

static bool isAltPressed() {
	return isKeyPressed(VK_LMENU) || isKeyPressed(VK_RMENU);
}

static bool isWindowsPressed() {
	return isKeyPressed(VK_LWIN) || isKeyPressed(VK_RWIN);
}

static int getModifier() {
	return (0 | (isShiftPressed() ? MOD_SHIFT : 0) | (isControlPressed() ? MOD_CONTROL : 0) | (isAltPressed() ? MOD_ALT : 0) | (isWindowsPressed() ? MOD_WIN : 0));
}

static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;

	switch (wParam) {
	case WM_KEYDOWN:
		envi->CallStaticVoidMethod(keyboardReceiverClass, m_keyPress, (long)key->vkCode, (long)getModifier());
		break;
	case WM_KEYUP:
		envi->CallStaticVoidMethod(keyboardReceiverClass, m_keyRelease, (long)key->vkCode, (long)getModifier());
		break;
	}

	auto value = CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	return block ? 1 : value;
}

void startKeyHooking(JNIEnv* env) {
	if (hooking || keyboardHook != NULL) return;

	hooking = true;

	envi = env;
	keyboardReceiverClass = envi->FindClass("crossplatformapi/main/keyboard/KeyEventReceiver");
	m_keyPress = envi->GetStaticMethodID(keyboardReceiverClass, "press", "(JJ)V");
	m_keyRelease = envi->GetStaticMethodID(keyboardReceiverClass, "release", "(JJ)V");
	m_keyHotKey = envi->GetStaticMethodID(keyboardReceiverClass, "pressHotKey", "(I)V");

	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) && hooking) { //TODO break GetMessage and not wait for input key (on unregister)
		if (msg.message == WM_HOTKEY) {
			//TODO
			envi->CallStaticVoidMethod(keyboardReceiverClass, m_keyHotKey, (int)msg.wParam, (int)msg.message, (int)(msg.lParam >> 16), (int)(msg.lParam & 0xffff));
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(keyboardHook);
	keyboardHook = NULL;
}

void setKeyHooking(bool value) {
	hooking = value;
	//UINT_PTR timerId = SetTimer(NULL, NULL, 10, NULL);
	//KillTimer(NULL, timerId);
}

void setKeyBlock(bool value) {
	block = value;
}