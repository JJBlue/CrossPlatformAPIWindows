#include "pch.h"

#include "crossplatformapi_jni_mouse_NativeMouse.h"
#include "mouse.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_press(JNIEnv*, jclass, jint button) {
	pressMouse(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_release(JNIEnv*, jclass, jint button) {
	releaseMouse(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_click(JNIEnv*, jclass, jint button) {
	pressMouse(button);
	releaseMouse(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_move(JNIEnv*, jclass, jlong x, jlong y) {
	//move(x, y);
	SetCursorPos(x, y);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_scroll(JNIEnv*, jclass, jint delta) {
	scroll(delta);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_hscroll(JNIEnv*, jclass, jint delta) {
	hscroll(delta);
}