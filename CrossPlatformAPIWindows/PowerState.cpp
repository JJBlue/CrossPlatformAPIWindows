#include "pch.h"

#include "crossplatformapi_jni_stats_PowerStates.h"
#include <windows.h>
#include <powrprof.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <WinUser.h>

#pragma comment(lib, "PowrProf.lib")

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_modernStandby(JNIEnv*, jclass) {
	
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_standby(JNIEnv*, jclass) {
	SetSuspendState(0, 1, 0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_hibernate(JNIEnv*, jclass) {
	SetSuspendState(1, 1, 0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_shutdown(JNIEnv*, jclass) {
	system("shutdown /s");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_reboot(JNIEnv*, jclass) {
	system("shutdown /r");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_logoff(JNIEnv*, jclass) {
	system("shutdown /l");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_lockScreen(JNIEnv*, jclass) {
	LockWorkStation();
}