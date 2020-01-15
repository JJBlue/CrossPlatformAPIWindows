#include "pch.h"

#include "screenshot.h"
#include "window.h"

static void setClipboardBitMap(HBITMAP hbmp) {
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();
}

void screenCapture(int x, int y, int w, int h, bitmapinfoclass* ba) {
	HDC hdcSource = GetDC(NULL);
	HDC hdcMemory = CreateCompatibleDC(hdcSource);

	int capX = GetDeviceCaps(hdcSource, HORZRES);
	int capY = GetDeviceCaps(hdcSource, VERTRES);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSource, w, h);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);

	BitBlt(hdcMemory, 0, 0, w, h, hdcSource, x, y, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);
	//setClipboardBitMap(hBitmap);

	BITMAP bmp;
	if (GetObject(hBitmap, sizeof(BITMAP), &bmp) == 0)
		cout << "ERROR load bitmap" << endl;

	int BigBps = bmp.bmBitsPixel / 8;
	LONG bigSize = bmp.bmHeight * bmp.bmWidth * BigBps;
	BYTE* bigBytes = new BYTE[bigSize];
	GetBitmapBits(hBitmap, bigSize, bigBytes);

	ba->height = bmp.bmHeight;
	ba->width = bmp.bmWidth;
	ba->size = bigSize;
	ba->pointer = bigBytes;

	DeleteDC(hdcSource);
	DeleteDC(hdcMemory);
	DeleteObject(hBitmap);
	DeleteObject(hBitmapOld);
	DeleteObject(&bmp);
}

void screenCapture(bool printBorder, bitmapinfoclass* ba) {
	HWND hWnd = getFocusWindow();

	if (hWnd != NULL) {
		LONG x = getWindowPositionLeft(hWnd);
		LONG y = getWindowPositionTop(hWnd);
		LONG w = getWindowWitdh(hWnd);
		LONG h = getWindowHeight(hWnd);

		screenCapture(x, y, w, h, ba);
	}
}

void screenshot(bool printBorder, bitmapinfoclass* ba) {
	//HWND hWnd = ::FindWindow(TEXT("Editor"), NULL);
	HWND hWnd = getFocusWindow();
	printInfo(hWnd);

	if (hWnd != NULL) {
		//create
		HDC hdcScreen = GetDC(NULL);
		HDC hdc = CreateCompatibleDC(hdcScreen);
		HBITMAP hbmp;

		if (printBorder) {
			RECT rc;
			GetWindowRect(hWnd, &rc);
			hbmp = CreateCompatibleBitmap(hdcScreen, rc.right - rc.left, rc.bottom - rc.top);
		}
		else {
			RECT rc;
			GetClientRect(hWnd, &rc);
			hbmp = CreateCompatibleBitmap(hdcScreen, rc.right - rc.left, rc.bottom - rc.top);
		}

		SelectObject(hdc, hbmp);

		//Print to memory hdc
		if (printBorder)
			PrintWindow(hWnd, hdc, 0);
		else
			PrintWindow(hWnd, hdc, PW_CLIENTONLY);

		//setClipboardBitMap(hbmp);
		//cout << "success copy to clipboard, please paste it to the 'mspaint'" << endl;

		BITMAP bmp;
		if (GetObject(hbmp, sizeof(BITMAP), &bmp) == 0)
			cout << "ERROR load bitmap" << endl;

		int BigBps = bmp.bmBitsPixel / 8;
		LONG bigSize = bmp.bmHeight * bmp.bmWidth * BigBps;
		BYTE* bigBytes = new BYTE[bigSize];
		GetBitmapBits(hbmp, bigSize, bigBytes);

		ba->height = bmp.bmHeight;
		ba->width = bmp.bmWidth;
		ba->size = bigSize;
		ba->pointer = bigBytes;

		//release
		DeleteDC(hdc);
		DeleteObject(hbmp);
		ReleaseDC(NULL, hdcScreen);
	}
	//cout << "it can't find any 'note' window" << endl;
}