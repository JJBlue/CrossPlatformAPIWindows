#include "pch.h"

#include "window.h"

#include <windows.h>
#include <string>
#include <vector>

long long hwndToLong(HWND hwnd) {
	return (long)(long)hwnd;
}

HWND longToHWND(long long id) {
	return (HWND) id;
}

//---Find Functions----

HWND getFocusWindow() {
	return GetForegroundWindow();
}

static BOOL CALLBACK allWindows(HWND hwnd, LPARAM lParam) {
	if (hwnd == NULL) return TRUE;

	if (IsWindowVisible(hwnd)) {
		std::vector<HWND>* fwc = (std::vector<HWND>*) lParam;
		fwc->push_back(hwnd);
	}
	return TRUE;
}

void getAllVisibleWindows(std::vector<HWND>* list) {
	EnumWindows(&allWindows, (LPARAM) list);
}

//---Set/Get HWND properties---

void getWindowTitle(HWND hwnd, std::wstring *title) {
	if (hwnd == NULL) return;

	int length = GetWindowTextLengthW(hwnd) + 1;
	wchar_t* wnd_title = new wchar_t[length];
	GetWindowTextW(hwnd, wnd_title, length);

	title->append(wnd_title);
}

std::string getWindowClassName(HWND hwnd) {
	char class_name[256 * 2];
	GetClassName(hwnd, (LPWSTR) class_name, sizeof(class_name) / 2);
	return class_name;
}

LONG getWindowWitdh(HWND hwnd) {
	RECT rc;
	GetClientRect(hwnd, &rc);
	return rc.right - rc.left;
}

LONG getWindowHeight(HWND hwnd) {
	RECT rc;
	GetClientRect(hwnd, &rc);
	return rc.bottom - rc.top;
}

LONG getWindowPositionLeft(HWND hwnd) {
	RECT rc;
	GetWindowRect(hwnd, &rc);
	WINDOWINFO info;
	info.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &info);

	return rc.left + info.cxWindowBorders;
}

LONG getWindowPositionRight(HWND hwnd) {
	RECT rc;
	GetWindowRect(hwnd, &rc);

	WINDOWINFO info;
	info.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &info);

	return rc.right + info.cxWindowBorders;
}

LONG getWindowPositionTop(HWND hwnd) {
	RECT rc;
	GetWindowRect(hwnd, &rc);

	WINDOWINFO info;
	info.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &info);

	return rc.top + info.cyWindowBorders;
}

LONG getWindowPositionBottom(HWND hwnd) {
	RECT rc;
	GetWindowRect(hwnd, &rc);

	WINDOWINFO info;
	info.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &info);

	return rc.bottom + info.cyWindowBorders;
}

void windowToFront(HWND hwnd) {
	SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void windowToBack(HWND hwnd) {
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void setTopMost(HWND hwnd, bool value) {
	SetWindowPos(hwnd, value ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void setWindowPosition(HWND hwnd, long x, long y) {
	SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void setWindowSize(HWND hwnd, long width, long height) {
	SetWindowPos(hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}