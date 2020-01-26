#pragma once

#include <Windows.h>
#include <vector>

HMONITOR longToMonitor(long long monitor);

long long monitorToLong(HMONITOR monitor);

HMONITOR getPrimaryMonitor();

HMONITOR getMonitor(int x, int y);

HMONITOR getMonitor(HWND hwnd);

void getArea(HMONITOR monitor, long long* x, long long* y, long long* width, long long* height);

void getWorkArea(HMONITOR monitor, long long* x, long long* y, long long* width, long long* height);

void getAllMonitors(std::vector<HMONITOR>* monitors);

void getDesktopResolution(long long* width, long long* height);

void getAllResolution(long long* width, long long* height);

bool isPrimary(HMONITOR monitor);

void setBrightness(HMONITOR monitor, DWORD brightness);

long getBrightness(HMONITOR monitor);

long getMinBrightness(HMONITOR monitor);

long getMaxBrightness(HMONITOR monitor);
