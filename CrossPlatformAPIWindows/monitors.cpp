#include "pch.h"

#include <vector>

HMONITOR longToMonitor(long long monitor) {
	return (HMONITOR)monitor;
}

long long monitorToLong(HMONITOR monitor) {
	return (long long)monitor;
}

HMONITOR getPrimaryMonitor() {
	const POINT ptZero = { 0, 0 };
	return MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
}

HMONITOR getMonitor(int x, int y) {
	const POINT point = { x, y };
	return MonitorFromPoint(point, MONITOR_DEFAULTTOPRIMARY);
}

HMONITOR getMonitor(HWND hwnd) {
	return MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
}

static MONITORINFO info(HMONITOR hmonitor) {
	/*
		DWORD cbSize;
		RECT  rcMonitor;
		RECT  rcWork;
		DWORD dwFlags;
	*/
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hmonitor, &mi);
	return mi;
}

void getArea(HMONITOR monitor, long long* x, long long* y, long long* width, long long* height) {
	MONITORINFO mi = info(monitor);
	if(x != NULL) *x = mi.rcMonitor.left;
	if(y != NULL) *y = mi.rcMonitor.top;
	if(width != NULL) *width = (long long) mi.rcMonitor.right - (long long) mi.rcMonitor.left;
	if(height != NULL) *height = (long long) mi.rcMonitor.bottom - (long long) mi.rcMonitor.top;
}

void getWorkArea(HMONITOR monitor, long long* x, long long* y, long long* width, long long* height) {
	MONITORINFO mi = info(monitor);
	if (x != NULL) *x = mi.rcWork.left;
	if (y != NULL) *y = mi.rcWork.top;
	if (width != NULL) *width = (long long)mi.rcWork.right - (long long)mi.rcWork.left;
	if (height != NULL) *height = (long long)mi.rcWork.bottom - (long long)mi.rcWork.top;
}

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
	std::vector<HMONITOR>* monitors = (std::vector<HMONITOR>*) dwData;
	monitors->push_back(hMonitor);
	return TRUE;
}

void getAllMonitors(std::vector<HMONITOR>* monitors) {
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM) monitors);
}

void getDesktopResolution(long long *width, long long *height) {
	*width = GetSystemMetrics(SM_CXSCREEN);
	*height = GetSystemMetrics(SM_CYSCREEN);
}

void getAllResolution(long long* width, long long* height) {
	*width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	*height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

bool isPrimary(HMONITOR monitor) {
	MONITORINFO mi = info(monitor);
	return (mi.dwFlags | MONITORINFOF_PRIMARY) == mi.dwFlags;
}