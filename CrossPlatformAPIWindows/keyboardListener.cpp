#include "pch.h"

#include "crossplatformapi_jni_keyboard_KeyboardListener.h"

bool hooking = false;
HHOOK keyboardHook;
HANDLE hThread;

JNIEnv* envi;
jclass clazz;

jmethodID methodHookKey;
jmethodID hk;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT) lParam;
	envi->CallStaticVoidMethod(clazz, methodHookKey, (int) wParam, (int) key->vkCode, (int) key->flags);
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

DWORD WINAPI hotkeyThread(LPVOID lpParm){
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) && hooking) {
		if (msg.message == WM_HOTKEY) {
			envi->CallStaticVoidMethod(clazz, hk, (int) msg.wParam, (int) msg.message, (int) (msg.lParam >> 16), (int) (msg.lParam & 0xffff));
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

JNIEXPORT void JNICALL Java_components_dll_keys_CHeader_startHooking(JNIEnv* env, jobject c) {
	hooking = true;

	envi = env;
	clazz = envi->FindClass("crossplatformapi/main/keyboard/KeyEventReceiver");
	methodHookKey = envi->GetStaticMethodID(clazz, "hookedKey", "(III)V"); //Ljava/lang/Integer
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0); //WH_KEYBOARD_LL
	hk = envi->GetStaticMethodID(clazz, "hookedHotKey", "(IIII)V");

	DWORD dwThread;
	hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) hotkeyThread, NULL, NULL, &dwThread);
}

JNIEXPORT void JNICALL Java_components_dll_keys_CHeader_stopHooking(JNIEnv* env, jobject c) {
	hooking = false;

	if (hThread != NULL) {
		DWORD exitCode;
		if (GetExitCodeThread(hThread, &exitCode) != 0) {
			ExitThread(exitCode);
			CloseHandle(hThread);
		}

		hThread = NULL;
	}

	if (keyboardHook != NULL) {
		UnhookWindowsHookEx(keyboardHook);
		keyboardHook = NULL;
	}
}