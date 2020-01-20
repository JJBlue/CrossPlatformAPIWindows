#include "pch.h"

#include "crossplatformapi_jni_display_NativeDisplay.h"
#include "monitors.h"
#include "window.h"

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getPrimaryDisplay(JNIEnv*, jclass) {
	return monitorToLong(getPrimaryMonitor());
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getDisplay__J(JNIEnv*, jclass, jlong window) {
	return monitorToLong(getMonitor(longToHWND(window)));
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getDisplay__JJ(JNIEnv*, jclass, jlong x, jlong y) {
	return monitorToLong(getMonitor(x, y));
}

JNIEXPORT jlongArray JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getDisplays(JNIEnv* env, jclass) {
	std::vector<HMONITOR> list;
	getAllMonitors(&list);

	jlongArray ids = env->NewLongArray(list.size());
	jsize size = 0;

	for (HMONITOR monitor : list) {
		jlong ar[1];
		ar[0] = (jlong)monitorToLong(monitor);
		env->SetLongArrayRegion(ids, size, 1, ar);
		size++;
	}

	list.clear();

	return ids;
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_display_NativeDisplay_isPrimary(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	return isPrimary(hmonitor);
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getX(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getArea(hmonitor, &value, NULL, NULL, NULL);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getY(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getArea(hmonitor, NULL, &value, NULL, NULL);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWidth(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getArea(hmonitor, NULL, NULL, &value, NULL);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getHeight(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getArea(hmonitor, NULL, NULL, NULL, &value);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkX(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getWorkArea(hmonitor, &value, NULL, NULL, NULL);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkY(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getWorkArea(hmonitor, NULL, &value, NULL, NULL);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkWidth(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getWorkArea(hmonitor, NULL, NULL, &value, NULL);
	return value;
}

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkHeight(JNIEnv*, jclass, jlong monitor) {
	HMONITOR hmonitor = longToMonitor(monitor);
	jlong value;
	getWorkArea(hmonitor, NULL, NULL, NULL, &value);
	return value;
}


