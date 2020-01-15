#include "pch.h"

#include "window.h"

#include <windows.h>
#include <string>

#include <vector>
#include <iostream>

long long hwndToLong(HWND hwnd) {
	return (long)(long)hwnd;
}

HWND longToHWND(long long id) {
	return (HWND) id;
}

void getWindowTitle(HWND hwnd, windowTitle* wt) {
	if (hwnd == NULL || wt == NULL) return;

	int length = GetWindowTextLengthW(hwnd) + 1;
	wchar_t* wnd_title = new wchar_t[length];
	
	GetWindowTextW(hwnd, wnd_title, length);

	wt->wtitle = wnd_title;
	wt->length = length;
}


//---Find Functions----

HWND getFocusWindow() {
	return GetForegroundWindow();
}

static BOOL CALLBACK findAnWindow(HWND hwnd, LPARAM lParam) {
	if (hwnd == NULL) return TRUE;

	if (IsWindowVisible(hwnd)) {
		findWindowClass* fwc = (findWindowClass*)lParam;

		windowTitle wt;
		getWindowTitle(hwnd, &wt);

		if (wt.length > 1) {
			try {
				std::wstring title = wt.wtitle;

				if (title.find(fwc->wtitle.c_str()) != std::wstring::npos) {
					fwc->hwnd = hwnd;
					fwc->wtitle = title;
					return FALSE;
				}
			} catch (const std::exception&) {}
		}

		wt.Delete();
	}
	return TRUE;
}

HWND findWindow(const wchar_t* titleArray) {
	HWND hwnd = FindWindowW(NULL, titleArray);
	if (hwnd != NULL)
		return hwnd;

	findWindowClass fwc;
	fwc.wtitle = std::wstring(titleArray);
	EnumWindows(&findAnWindow, (LPARAM) &fwc);

	return fwc.hwnd;
}

static BOOL CALLBACK getWindowTitles(HWND hwnd, LPARAM lParam) {
	if (hwnd == NULL) return TRUE;

	if (IsWindowVisible(hwnd)) {
		std::vector<windowTitle>* titles = (std::vector<windowTitle>*)lParam;

		windowTitle wt;
		getWindowTitle(hwnd, &wt);

		if (wt.length > 1)
			titles->insert(titles->begin(), wt);
	}
	return TRUE;
}

void getWindowTitles(std::vector<windowTitle>* titles) {
	EnumWindows(&getWindowTitles, (LPARAM)titles);
}

//---Set/Get HWND properties---

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