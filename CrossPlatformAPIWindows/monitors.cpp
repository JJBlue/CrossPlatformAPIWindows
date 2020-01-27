#include "pch.h"

#include <vector>
#include <highlevelmonitorconfigurationapi.h>

//#include <iostream>
#include "helper.h"

#pragma comment(lib, "Dxva2.lib") //highlevelmonitorconfigurationapi.h

#include <Ntddvdeo.h>
#include <winioctl.h>

HMONITOR longToMonitor(long long monitor) {
	return (HMONITOR)monitor;
}

long long monitorToLong(HMONITOR monitor) {
	return (long long)monitor;
}

static bool getPhysicalMonitor(HMONITOR monitor, HANDLE *physicalMonitor) {
	DWORD amount;

	if (!GetNumberOfPhysicalMonitorsFromHMONITOR(monitor, &amount) || amount <= 0) {
		printError();
		return FALSE;
	}

	PHYSICAL_MONITOR* monitors = new PHYSICAL_MONITOR[amount];

	if (!GetPhysicalMonitorsFromHMONITOR(monitor, amount, monitors)) {
		printError();
		return FALSE;
	}

	*physicalMonitor = monitors[0].hPhysicalMonitor;

	if (physicalMonitor == INVALID_HANDLE_VALUE) {
		printError("Invalid Handle in getPhysicalMonitor(...)");
		return FALSE;
	}

	return TRUE;
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

static bool setBrightnessNormal(HANDLE pmonitor, DWORD brightness) {
	if (SetMonitorBrightness(pmonitor, brightness)) {
		printError();
		return TRUE;
	}
	return FALSE;
}

static bool setBrightnessLCD(HANDLE physicalMonitor, DWORD brightness) {
	HANDLE lcd_handle = CreateFileW(L"\\\\.\\LCD", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (lcd_handle == INVALID_HANDLE_VALUE) {
		printError("error invalid handle");
		return FALSE;
	}

	DISPLAY_BRIGHTNESS display_brightness;
	display_brightness.ucDisplayPolicy = DISPLAYPOLICY_BOTH;
	display_brightness.ucACBrightness = brightness;
	display_brightness.ucDCBrightness = brightness;

	DWORD ret;
	bool result = DeviceIoControl(lcd_handle, IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS, &display_brightness, sizeof(display_brightness), NULL, 0, &ret, NULL);

	if (!result) {
		printError();
		return FALSE;
	}

	CloseHandle(lcd_handle);

	return TRUE;
}

static bool setBrightnessDisplay(HMONITOR monitor, DWORD brightness) {
	HANDLE pmonitor;
	if (!getPhysicalMonitor(monitor, &pmonitor)) {
		return FALSE;
	}

	if (setBrightnessNormal(pmonitor, brightness)) {
		return TRUE;
	}

	if (setBrightnessLCD(pmonitor, brightness)) {
		return TRUE;
	}

	return FALSE;
}

void setBrightness(HMONITOR monitor, DWORD brightness) {
	setBrightnessDisplay(monitor, brightness);
}

static bool getBrighnessNormal(HANDLE physicalMonitor, LPDWORD pdwMinimumBrightness, LPDWORD pdwCurrentBrightness, LPDWORD pdwMaximumBrightness) {
	if (!GetMonitorBrightness(physicalMonitor, pdwMinimumBrightness, pdwCurrentBrightness, pdwMaximumBrightness)) {
		return FALSE;
	}
	return TRUE;
}

static bool getBrightnessLCD(HANDLE physicalMonitor, LPDWORD pdwMinimumBrightness, LPDWORD pdwCurrentBrightness, LPDWORD pdwMaximumBrightness) {
	//BrightnessResult brightness_result;
	HANDLE lcd_handle = CreateFileW(L"\\\\.\\LCD", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (lcd_handle == INVALID_HANDLE_VALUE) {
		printError("Invalid Handle in getBrightnessLCD(...)");
		return FALSE;
	}

	DISPLAY_BRIGHTNESS brightness;
	DWORD ret;
	byte buffer[256];
	
	//Supported Brightness
	bool result = DeviceIoControl(lcd_handle, IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS, NULL, 0, buffer, sizeof(buffer), &ret, NULL);

	if (!result) {
		printError();
		return FALSE;
	}

	*pdwMinimumBrightness = -1;
	*pdwCurrentBrightness = -1;
	*pdwMaximumBrightness = -1;

	for (DWORD i = 0; i < ret; i++) {
		DWORD value = buffer[i];

		if (value < *pdwMinimumBrightness || *pdwMinimumBrightness == -1) {
			*pdwMinimumBrightness = value;
		}

		if (value > *pdwMaximumBrightness || *pdwMaximumBrightness == -1) {
			*pdwMaximumBrightness = value;
		}
	}

	//Display Brightness
	result = DeviceIoControl(lcd_handle, IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS, NULL, 0, &brightness, sizeof(brightness), &ret, NULL);

	if (!result) {
		printError();
		return FALSE;
	}

	if (brightness.ucDisplayPolicy == DISPLAYPOLICY_AC) {
		*pdwCurrentBrightness = brightness.ucACBrightness;
	} else if (brightness.ucDisplayPolicy == DISPLAYPOLICY_DC) {
		*pdwCurrentBrightness = brightness.ucDCBrightness;
	} else if (brightness.ucDisplayPolicy == DISPLAYPOLICY_BOTH) {
		*pdwCurrentBrightness = brightness.ucACBrightness;
	}

	CloseHandle(lcd_handle);

	return TRUE;
}

static bool getBrightnessInformation(HMONITOR monitor, LPDWORD pdwMinimumBrightness, LPDWORD pdwCurrentBrightness, LPDWORD pdwMaximumBrightness) {
	HANDLE physicalMonitor;

	if (!getPhysicalMonitor(monitor, &physicalMonitor)) {
		return -1;
	}
	
	if (getBrighnessNormal(physicalMonitor, pdwMinimumBrightness, pdwCurrentBrightness, pdwMaximumBrightness)) {
		return TRUE;
	}
	//printError();

	if (getBrightnessLCD(physicalMonitor, pdwMinimumBrightness, pdwCurrentBrightness, pdwMaximumBrightness)) {
		return TRUE;
	}

	return FALSE;
}

long getBrightness(HMONITOR monitor) {
	DWORD min, cur, max;

	if (getBrightnessInformation(monitor, &min, &cur, &max)) {
		return cur;
	}

	return -1;
}

long getMinBrightness(HMONITOR monitor) {
	DWORD min, cur, max;
	GetMonitorBrightness(monitor, &min, &cur, &max);
	return min;
}

long getMaxBrightness(HMONITOR monitor) {
	DWORD min, cur, max;
	GetMonitorBrightness(monitor, &min, &cur, &max);
	return max;
}

void turnOffMonitors() {
	HWND hwnd = GetForegroundWindow();

	if (hwnd == NULL) {
		hwnd = HWND_BROADCAST;
	}

	SendMessage(hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
}

void turnOnMonitors() {
	HWND hwnd = GetForegroundWindow();

	if (hwnd == NULL) {
		hwnd = HWND_BROADCAST;
	}

	SendMessage(hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
}