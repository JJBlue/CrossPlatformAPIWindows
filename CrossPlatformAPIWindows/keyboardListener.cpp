#include "pch.h"

#include "crossplatformapi_jni_keyboard_KeyboardListener.h"

#include <iostream> //Ein und Ausgabe

static bool hooking = false;
static HHOOK keyboardHook;

static JNIEnv* envi;
static jclass clazz;

static jmethodID m_hookKey, m_hotKey;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT) lParam;
	envi->CallStaticVoidMethod(clazz, m_hookKey, (int)wParam, (int)key->vkCode, (int)key->flags);
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_registerListener(JNIEnv* env, jclass) {
	envi = env;
	clazz = envi->FindClass("crossplatformapi/main/keyboard/KeyEventReceiver");
	m_hookKey = envi->GetStaticMethodID(clazz, "hookedKey", "(III)V"); //Ljava/lang/Integer
	m_hotKey = envi->GetStaticMethodID(clazz, "hookedHotKey", "(IIII)V");

	hooking = true;
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) && hooking) {
		if (msg.message == WM_HOTKEY) {
			envi->CallStaticVoidMethod(clazz, m_hotKey, (int) msg.wParam, (int) msg.message, (int) (msg.lParam >> 16), (int) (msg.lParam & 0xffff));
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