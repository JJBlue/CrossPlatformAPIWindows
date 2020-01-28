#include "pch.h"

#include "crossplatformapi_jni_battery_NativeBatteryListener.h"
#include "batteryListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_battery_NativeBatteryListener_register(JNIEnv* env, jclass) {
	registerPowerListener(env);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_battery_NativeBatteryListener_unregister(JNIEnv* env, jclass) {
	unregisterPowerListener(env);
}