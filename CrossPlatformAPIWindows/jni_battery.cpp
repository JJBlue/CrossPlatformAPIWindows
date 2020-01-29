#include "pch.h"

#include "crossplatformapi_jni_battery_NativeBattery.h"
#include "battery.h"

JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_battery_NativeBattery_getCapacityInPercent(JNIEnv*, jclass) {
	return getCurrentBatteryInPercent();
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_battery_NativeBattery_isPowerOnLine(JNIEnv*, jclass) {
	return isCharging();
}

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_battery_NativeBattery_isBatterySaverOn(JNIEnv*, jclass) {
	return isBatterySaverOn();
}