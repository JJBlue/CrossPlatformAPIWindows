#pragma once

#include <string>
#include <vector>

long long hwndToLong(HWND hwnd);

HWND longToHWND(long long id);

void getWindowTitle(HWND hwnd, std::wstring*);

HWND getFocusWindow();

void getAllVisibleWindows(std::vector<HWND>* list);

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