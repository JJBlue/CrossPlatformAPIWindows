#include "pch.h"

#include "crossplatformapi_jni_battery_BatteryListener.h"
#include "batteryListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_battery_BatteryListener_register(JNIEnv* env, jclass) {
	registerPowerListener(env);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_battery_BatteryListener_unregister(JNIEnv* env, jclass) {
	unregisterPowerListener(env);
}