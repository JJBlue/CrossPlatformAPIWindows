#include "pch.h"

#include "crossplatformapi_jni_keyboard_KeyboardListener.h"

static bool hooking = false;
static bool block = false;
static HHOOK keyboardHook;

static JNIEnv* envi;
static jclass clazz;

static jmethodID m_press, m_release, m_pressHotKey, m_releaseHotkey;

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

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT) lParam;

	switch (wParam) {
		case WM_KEYDOWN:
			envi->CallStaticVoidMethod(clazz, m_press, (long)key->vkCode, isControlPressed(), isWindowsPressed(), isAltPressed(), isShiftPressed());
			break;
		case WM_KEYUP:
			envi->CallStaticVoidMethod(clazz, m_release, (long)key->vkCode, isControlPressed(), isWindowsPressed(), isAltPressed(), isShiftPressed());
			break;
	}

	auto value = CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	return block ? 1 : value;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_registerListener(JNIEnv* env, jclass) {
	envi = env;
	clazz = envi->FindClass("crossplatformapi/main/keyboard/KeyEventReceiver");
	m_press = envi->GetStaticMethodID(clazz, "press", "(JZZZZ)V");
	m_release = envi->GetStaticMethodID(clazz, "release", "(JZZZZ)V");
	m_pressHotKey = envi->GetStaticMethodID(clazz, "pressHotKey", "(I)V");
	m_releaseHotkey = envi->GetStaticMethodID(clazz, "releaseHotKey", "(I)V");

	hooking = true;
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) && hooking) { //TODO break GetMessage and not wait for input key (on unregister)
		if (msg.message == WM_HOTKEY) {
			//TODO
			envi->CallStaticVoidMethod(clazz, m_pressHotKey, (int) msg.wParam, (int) msg.message, (int) (msg.lParam >> 16), (int) (msg.lParam & 0xffff));
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(keyboardHook);
	keyboardHook = NULL;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_unregisterListener(JNIEnv*, jclass) {
	hooking = false;
	//UINT_PTR timerId = SetTimer(NULL, NULL, 10, NULL);
	//KillTimer(NULL, timerId);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_block(JNIEnv*, jclass) {
	block = true;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_unblock(JNIEnv*, jclass) {
	block = false;
}