#include "pch.h"


#include "mouse.h"

#include <winuser.h>

void pressMouse(int button) {
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

void releaseMouse(int button) {
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

void moveMouse(int x, int y) {
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dx = (x * 65536) / GetSystemMetrics(SM_CXSCREEN);
	ip.mi.dy = (y * 65536) / GetSystemMetrics(SM_CYSCREEN);
	ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &ip, sizeof(INPUT));
}

void scroll(int delta) {
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

void hscroll(int delta) {
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