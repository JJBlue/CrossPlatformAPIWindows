#include "pch.h"

#include "crossplatformapi_jni_keyboard_NativeKeyboard.h"
#include "keyboard.h"

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_registerHotKey(JNIEnv*, jclass, jint id, jint modifires, jint key) {
	return (bool)RegisterHotKey(NULL, id, modifires, key);
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_unregisterHotKey(JNIEnv*, jclass, jint id) {
	return UnregisterHotKey(NULL, id);
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_isKeyPressed(JNIEnv*, jclass, jint key) {
	return isKeyPressed(key);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_press(JNIEnv*, jclass, jint key) {
	pressScanKey(key);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_release(JNIEnv*, jclass, jint key) {
	releaseScanKey(key);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_write(JNIEnv* env, jclass, jstring text) {
	jboolean isCopy;
	const wchar_t* nativeString = (wchar_t*)env->GetStringChars(text, &isCopy);

	write(nativeString);

	if (isCopy == JNI_TRUE) {
		env->ReleaseStringChars(text, (const jchar*) nativeString);
	}
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_press2(JNIEnv*, jclass, jint key) {
	pressKey(key);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_release2(JNIEnv*, jclass, jint key) {
	releaseKey(key);
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

	WORD low_word = LOWORD(hkl);
	WORD high_word = HIWORD(hkl);

	int subLanguageID = SUBLANGID(low_word);
	int primaryLanguageID = SUBLANGID(low_word);

	std::cout << hkl << " " << low_word << " " << high_word << std::endl;

	return NULL;
}