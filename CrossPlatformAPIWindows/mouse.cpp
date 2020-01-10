#include "pch.h"

#include "crossplatformapi_jni_mouse_Mouse.h"

#include <winuser.h>

static void press(int button) {
	switch (button) {
		case 0:
			button = MOUSEEVENTF_LEFTDOWN;
			break;
		case 1:
			button = MOUSEEVENTF_RIGHTDOWN;
			break;
		case 2:
			button = MOUSEEVENTF_MIDDLEDOWN;
			break;
		case 3:
			button = MOUSEEVENTF_XDOWN | XBUTTON1;
			break;
		case 4:
			button = MOUSEEVENTF_XDOWN | XBUTTON2;
			break;
	}

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
	Inputs[0].mi.dx = (x * 65536) / GetSystemMetrics(SM_CXSCREEN);
	Inputs[0].mi.dy = (y * 65536) / GetSystemMetrics(SM_CYSCREEN);
	Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, Inputs, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_press(JNIEnv*, jclass, jint button) {
	press(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_release(JNIEnv*, jclass, jint button) {
	release(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_click(JNIEnv*, jclass, jint button) {
	press(button);
	release(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_Mouse_move(JNIEnv*, jclass, jlong x, jlong y) {
	move(x, y);
}