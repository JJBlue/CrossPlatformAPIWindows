#include "pch.h"

#include "crossplatformapi_jni_window_NativeWindow.h"
#include "window.h"

#include <vector>

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getWindowInForeground(JNIEnv*, jclass) {
	HWND hwnd = getFocusWindow();
	return hwndToLong(hwnd);
}

JNIEXPORT jlongArray JNICALL Java_crossplatformapi_jni_window_NativeWindow_getVisibleWindows(JNIEnv* env, jclass) {
	std::vector<HWND> list;
	getAllVisibleWindows(&list);
	
	jlongArray ids = env->NewLongArray(list.size());
	jsize size = 0;

	for (HWND hwnd : list) {
		jlong ar[1];
		ar[0] = (jlong) hwndToLong(hwnd);
		env->SetLongArrayRegion(ids, size, 1, ar);
		size++;
	}

	list.clear();

	return ids;
}

JNIEXPORT jstring JNICALL Java_crossplatformapi_jni_window_NativeWindow_getTitle(JNIEnv* env, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	std::wstring title;
	getWindowTitle(hwnd, &title);
	jstring s = env->NewString((const jchar*) title.c_str(), title.length());
	return s;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getXPosition(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	return getWindowPositionLeft(hwnd);
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getYPosition(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	return getWindowPositionTop(hwnd);
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getWidth(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	return getWindowWitdh(hwnd);
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getHeight(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	return getWindowHeight(hwnd);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindow_setMaximize(JNIEnv*, jclass, jlong, jlong) {
	//TODO
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindow_setTopMost(JNIEnv*, jclass, jlong window, jboolean value) {
	HWND hwnd = longToHWND(window);
	setTopMost(hwnd, value);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindow_setSize(JNIEnv*, jclass, jlong window, jlong width, jlong height) {
	HWND hwnd = longToHWND(window);
	setWindowSize(hwnd, width, height);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindow_setPosition(JNIEnv*, jclass, jlong window, jlong x , jlong y) {
	HWND hwnd = longToHWND(window);
	setWindowPosition(hwnd, x, y);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindow_toFront(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	windowToFront(hwnd);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindow_toBack(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	windowToBack(hwnd);
}