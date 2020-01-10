#include "pch.h"

#include "crossplatformapi_jni_mouse_Mouse.h"

static void press(int button) {
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &ip, sizeof(INPUT));
}

static void release(int button) {
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &ip, sizeof(INPUT));
}

static void move(int x, int y) {
	INPUT Inputs[1] = { 0 };
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dx = x;
	Inputs[0].mi.dy = y;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, Inputs, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_press(JNIEnv*, jclass) {
	press(0); //TODO
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_release(JNIEnv*, jclass) {
	release(0); //TODO
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_click(JNIEnv*, jclass) {
	press(0); //TODO
	release(0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_move(JNIEnv*, jclass, jlong x, jlong y) {
	move(x, y);
}