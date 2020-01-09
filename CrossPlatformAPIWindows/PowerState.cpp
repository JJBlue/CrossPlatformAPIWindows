#include "pch.h"

#include "crossplatformapi_jni_stats_PowerStates.h"
#include <windows.h>
#include <powrprof.h>

#pragma comment(lib, "PowrProf.lib")

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_modernStandby(JNIEnv*, jobject) {
	
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_standby(JNIEnv*, jobject) {
	SetSuspendState(0, 1, 0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_hibernate(JNIEnv*, jobject) {
	SetSuspendState(1, 1, 0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_shutdown(JNIEnv*, jobject) {

}