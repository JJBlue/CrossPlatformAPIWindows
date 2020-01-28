#include "pch.h"

#include "crossplatformapi_jni_keyboard_NativeKeyboardListener.h"
#include "keyboardListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboardListener_register(JNIEnv* env, jclass) {
	startKeyHooking(env);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboardListener_unregister(JNIEnv*, jclass) {
	setKeyHooking(false);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboardListener_block(JNIEnv*, jclass) {
	setKeyBlock(true);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboardListener_unblock(JNIEnv*, jclass) {
	setKeyBlock(false);
}