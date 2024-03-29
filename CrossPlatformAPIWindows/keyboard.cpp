﻿#include "pch.h"

#include <string>
#include <dinput.h>
#include <map>

void pressKey(int key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = 0; //keydown
	SendInput(1, &ip, sizeof(INPUT));
}

void pressScanKey(int key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wScan = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
	ip.ki.wVk = 0; // Ignored
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; //keydown
	SendInput(1, &ip, sizeof(INPUT));
}

void releaseKey(int key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void releaseScanKey(int key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wScan = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
	ip.ki.wVk = 0; // Ignored
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; //keydown
	SendInput(1, &ip, sizeof(INPUT));
}

void write(std::wstring text) {
	for (auto ch : text) {
		INPUT input = {0};
		input.type = INPUT_KEYBOARD;
		input.ki.dwFlags = KEYEVENTF_UNICODE;
		input.ki.wScan = ch;
		SendInput(1, &input, sizeof(INPUT));

		input.ki.dwFlags |= KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
	}
}

bool isKeyPressed(int key) {
	return GetKeyState(key) & 0x8000;
}