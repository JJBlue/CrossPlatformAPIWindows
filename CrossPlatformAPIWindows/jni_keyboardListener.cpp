#include "pch.h"

#include "crossplatformapi_jni_keyboard_KeyboardListener.h"
#include "keyboardListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_KeyboardListener_registerListener(JNIEnv* env, jclass) {
	envi = env;
	keyboardReceiverClass = envi->FindClass("crossplatformapi/main/keyboard/KeyEventReceiver");
	m_keyPress = envi->GetStaticMethodID(keyboardReceiverClass, "press", "(JJ)V");
	m_keyRelease = envi->GetStaticMethodID(keyboardReceiverClass, "release", "(JJ)V");
	m_keyHotKey = envi->GetStaticMethodID(keyboardReceiverClass, "pressHotKey", "(I)V");

	startKeyHooking();
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