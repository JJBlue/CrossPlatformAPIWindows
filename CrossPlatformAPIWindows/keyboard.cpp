#include "pch.h"

#include "crossplatformapi_jni_keyboard_NativeKeyboard.h"

void press(int key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = 0; //keydown
	SendInput(1, &ip, sizeof(INPUT));
}

void release(int key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_registerHotKey(JNIEnv*, jclass, jint id, jint modifires, jint key) {
	return (bool) RegisterHotKey(NULL, id, modifires, key);
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_unregisterHotKey(JNIEnv*, jclass, jint id) {
	return UnregisterHotKey(NULL, id);
}

JNIEXPORT jshort JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_getKeyState(JNIEnv*, jclass, jint key) {
	return GetKeyState(key);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_pressKey(JNIEnv*, jclass, jint key) {
	press(key);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_releaseKey(JNIEnv*, jclass, jint key) {
	release(key);
}

#include <iostream>

JNIEXPORT jstring JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_getKeyboardLayout(JNIEnv*, jclass) {
	/*
		The return value is the input locale identifier for the thread.
		The low word contains a Language Identifier for the input language
		and the high word contains a device handle to the physical layout of the keyboard.
	*/
	DWORD id = GetCurrentThreadId();
	HKL hkl = GetKeyboardLayout(id);

	//SUBLANG_HEBREW_ISRAEL;

	WORD low_word = LOWORD(hkl);
	WORD high_word = HIWORD(hkl);

	int subLanguageID = SUBLANGID(low_word);
	int primaryLanguageID = SUBLANGID(low_word);

	std::cout << hkl << low_word << " " << " " << subLanguageID << " " << primaryLanguageID << std::endl;

	return NULL;
}