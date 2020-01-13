#include "pch.h"

#include "crossplatformapi_jni_mouse_NativeMouse.h"

#include <winuser.h>

static void press(int button) {
	switch (button) {
		case VK_LBUTTON:
			button = MOUSEEVENTF_LEFTDOWN;
			break;
		case VK_RBUTTON:
			button = MOUSEEVENTF_RIGHTDOWN;
			break;
		case VK_MBUTTON:
			button = MOUSEEVENTF_MIDDLEDOWN;
			break;
		case VK_XBUTTON1:
			button = MOUSEEVENTF_XDOWN | XBUTTON1;
			break;
		case VK_XBUTTON2:
			button = MOUSEEVENTF_XDOWN | XBUTTON2;
			break;
	}

	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &ip, sizeof(INPUT));
}

static void release(int button) {
	switch (button) {
	case VK_LBUTTON:
		button = MOUSEEVENTF_LEFTUP;
		break;
	case VK_RBUTTON:
		button = MOUSEEVENTF_RIGHTUP;
		break;
	case VK_MBUTTON:
		button = MOUSEEVENTF_MIDDLEUP;
		break;
	case VK_XBUTTON1:
		button = MOUSEEVENTF_XUP | XBUTTON1;
		break;
	case VK_XBUTTON2:
		button = MOUSEEVENTF_XUP | XBUTTON2;
		break;
	default:
		if (button > XBUTTON2) {
			button = MOUSEEVENTF_XUP | (button - (0x05 - 1));
			break;
		}
	}

	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &ip, sizeof(INPUT));
}

static void move(int x, int y) {
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dx = (x * 65536) / GetSystemMetrics(SM_CXSCREEN);
	ip.mi.dy = (y * 65536) / GetSystemMetrics(SM_CYSCREEN);
	ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &ip, sizeof(INPUT));
}

static void scroll(int delta) {
	if (delta > WHEEL_DELTA)
		delta = WHEEL_DELTA;
	else if (delta < -WHEEL_DELTA)
		delta = -WHEEL_DELTA;

	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_WHEEL;
	ip.mi.mouseData = delta;
	ip.mi.time = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

static void hscroll(int delta) {
	if (delta > WHEEL_DELTA)
		delta = WHEEL_DELTA;
	else if (delta < -WHEEL_DELTA)
		delta = -WHEEL_DELTA;

	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_HWHEEL;
	ip.mi.mouseData = delta;
	ip.mi.time = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_press(JNIEnv*, jclass, jint button) {
	press(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_release(JNIEnv*, jclass, jint button) {
	release(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_click(JNIEnv*, jclass, jint button) {
	press(button);
	release(button);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_move(JNIEnv*, jclass, jlong x, jlong y) {
	move(x, y);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_scroll(JNIEnv*, jclass, jint delta) {
	scroll(delta);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouse_hscroll(JNIEnv*, jclass, jint delta) {
	hscroll(delta);
}