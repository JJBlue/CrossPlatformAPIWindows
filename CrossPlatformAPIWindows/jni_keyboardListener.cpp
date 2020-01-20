#include "pch.h"

#include "crossplatformapi_jni_keyboard_KeyboardListener.h"
#include "keyboardListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_registerListener(JNIEnv* env, jclass) {
	startKeyHooking(env);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_unregisterListener(JNIEnv*, jclass) {
	setKeyHooking(false);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_block(JNIEnv*, jclass) {
	setKeyBlock(true);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_unblock(JNIEnv*, jclass) {
	setKeyBlock(false);
}