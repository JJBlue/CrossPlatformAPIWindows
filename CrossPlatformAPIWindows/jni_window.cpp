#include "pch.h"

#include "crossplatformapi_jni_window_NativeWindow.h"
#include "window.h"

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getWindowInForeground(JNIEnv*, jclass) {
	HWND hwnd = getFocusWindow();
	return hwndToLong(hwnd);
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getWindowByTitle(JNIEnv*, jclass, jstring title) {
	//TODO
	return NULL;
}

JNIEXPORT jlongArray JNICALL Java_crossplatformapi_jni_window_NativeWindow_getVisibleWindows(JNIEnv*, jclass) {
	//TODO
	return NULL;
}

JNIEXPORT jstring JNICALL Java_crossplatformapi_jni_window_NativeWindow_getTitle(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	//TODO
	return NULL;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getXPosition(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	return 0; //TODO
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_window_NativeWindow_getYPosition(JNIEnv*, jclass, jlong window) {
	HWND hwnd = longToHWND(window);
	return 0; //TODO
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

/*
JNIEXPORT jstring JNICALL Java_components_dll_window_C_CHeader_getFocusedTitle(JNIEnv* env, jobject obj) {
	windowTitle wt;
	getForegroundWindowTitle(true, &wt);

	if (wt.wtitle != NULL) {
		wchar_t* title = wt.wtitle;
		jstring s = env->NewString((jchar*)title, (jsize)wt.length);
		return s;
	}
	return env->NewString((jchar*)"", (jsize)0);
}

JNIEXPORT jstring JNICALL Java_components_dll_window_C_CHeader_getTitle(JNIEnv* env, jobject obj, jstring title) {
	char* titleChar = (char*)env->GetStringChars(title, NULL);

	HWND hwnd = findWindow(titleChar);
	windowTitle wt;
	getWindowTitle(hwnd, false, &wt);

	if (wt.title == NULL)
		return NULL;

	jstring s = env->NewStringUTF(wt.title);

	return s;
}


JNIEXPORT jobject JNICALL Java_components_dll_window_C_CHeader_screenshoot(JNIEnv* env, jobject obj, jint x, jint y, jint w, jint h) {
	bitmapinfoclass ba;
	screenCapture((int)x, (int)y, (int)w, (int)h, &ba);

	jbyteArray result = env->NewByteArray(ba.size);
	env->SetByteArrayRegion(result, 0, ba.size, (const jbyte*)ba.pointer);
	delete[] ba.pointer;

	jclass cl = env->FindClass("components/dll/window/C/Picture");
	jmethodID m = env->GetStaticMethodID(cl, "konstruktor", "(JJ[B)Lcomponents/dll/window/C/Picture;");

	return env->CallStaticObjectMethod(cl, m, (jlong)0, (jlong)0, result);
}

JNIEXPORT jobject JNICALL Java_components_dll_window_C_CHeader_screenshootActiveWindow(JNIEnv* env, jobject obj) {
	bitmapinfoclass ba;
	screenCapture(true, &ba);

	jbyteArray result = env->NewByteArray(ba.size);
	env->SetByteArrayRegion(result, 0, ba.size, (const jbyte*)ba.pointer);
	delete[] ba.pointer;

	jclass cl = env->FindClass("components/dll/window/C/Picture");
	jmethodID m = env->GetStaticMethodID(cl, "konstruktor", "(JJ[B)Lcomponents/dll/window/C/Picture;");

	return env->CallStaticObjectMethod(cl, m, (jlong)0, (jlong)0, result);
}

JNIEXPORT jobject JNICALL Java_components_dll_window_C_CHeader_screenshootByeTitle(JNIEnv* env, jobject obj, jstring name) {
	char* title = (char*)env->GetStringChars(name, NULL);
	HWND hwnd = findWindow(title);
	bitmapinfoclass ba;
	screenCapture(true, &ba);

	jbyteArray result = env->NewByteArray(ba.size);
	env->SetByteArrayRegion(result, 0, ba.size, (const jbyte*)ba.pointer);
	delete[] ba.pointer;

	jclass cl = env->FindClass("components/dll/window/C/Picture");
	jmethodID m = env->GetStaticMethodID(cl, "konstruktor", "(JJ[B)Lcomponents/dll/window/C/Picture;");

	return env->CallStaticObjectMethod(cl, m, (jlong)0, (jlong)0, result);
}

JNIEXPORT jobjectArray JNICALL Java_components_dll_window_C_CHeader_allWindows(JNIEnv* env, jobject obj) {
	vector<windowTitle> wts;
	getWindowTitles(&wts);

	jclass classy = env->FindClass("java/lang/String");
	jobjectArray titles = env->NewObjectArray(wts.size(), classy, env->NewStringUTF(""));

	int count = 0;
	for (windowTitle wt : wts) {
		jstring s = env->NewString((jchar*)wt.wtitle, (jsize)wt.length);
		env->SetObjectArrayElement(titles, count++, s);
	}

	return titles;
}

*/