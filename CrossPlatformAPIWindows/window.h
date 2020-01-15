#pragma once

#include <string>

class windowTitle {
public:

	wchar_t* wtitle = NULL;
	int length;

	void Delete() {
		if (wtitle != NULL)
			delete[] wtitle;
	}
};

class findWindowClass {
public:
	std::wstring wtitle;
	HWND hwnd;
};

long long hwndToLong(HWND hwnd);

HWND longToHWND(long long id);

void getWindowTitle(HWND hwnd, windowTitle* wt);

HWND getFocusWindow();

HWND findWindow(const wchar_t* titleArray);

std::string getWindowClassName(HWND hwnd);

LONG getWindowWitdh(HWND hwnd);

LONG getWindowHeight(HWND hwnd);

LONG getWindowPositionLeft(HWND hwnd);

LONG getWindowPositionRight(HWND hwnd);

LONG getWindowPositionTop(HWND hwnd);

LONG getWindowPositionBottom(HWND hwnd);

void windowToFront(HWND hwnd);

void windowToBack(HWND hwnd);

void setTopMost(HWND hwnd, bool value);

void setWindowPosition(HWND hwnd, long x, long y);

void setWindowSize(HWND hwnd, long width, long height);