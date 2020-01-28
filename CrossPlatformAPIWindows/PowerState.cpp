#include "pch.h"

#include "crossplatformapi_jni_stats_NativePowerStates.h"
#include <windows.h>
#include <powrprof.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <WinUser.h>

#pragma comment(lib, "PowrProf.lib")

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_modernStandby(JNIEnv*, jclass) {
	
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_standby(JNIEnv*, jclass) {
	SetSuspendState(0, 1, 0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_hibernate(JNIEnv*, jclass) {
	SetSuspendState(1, 1, 0);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_shutdown(JNIEnv*, jclass) {
	system("shutdown /s");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_reboot(JNIEnv*, jclass) {
	system("shutdown /r");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_logoff(JNIEnv*, jclass) {
	system("shutdown /l");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_NativePowerStates_lockScreen(JNIEnv*, jclass) {
	LockWorkStation();
}