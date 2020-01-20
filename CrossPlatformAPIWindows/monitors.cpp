#include "pch.h"

#include <vector>

HMONITOR getPrimaryMonitor() {
	const POINT ptZero = { 0, 0 };
	return MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
}

HMONITOR getMonitor(int x, int y) {
	const POINT point = { x, y };
	return MonitorFromPoint(point, MONITOR_DEFAULTTOPRIMARY);
}

HMONITOR getNearestMonitor(HWND hwnd) {
	return MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
}

MONITORINFO info(int x, int y) {
	/*
		DWORD cbSize;
		RECT  rcMonitor;
		RECT  rcWork;
		DWORD dwFlags;
	*/
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(getMonitor(x, y), &mi);

	return mi;
}

MONITORINFO info(HMONITOR hmonitor) {
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

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);

	std::vector<MONITORINFO>* monitors = (std::vector<MONITORINFO>*) dwData;
	monitors->push_back(mi);

	return TRUE;
}

void getAllMonitors(std::vector<MONITORINFO>* monitors) {
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