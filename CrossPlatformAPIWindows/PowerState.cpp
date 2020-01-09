#include "pch.h"

#include "crossplatformapi_jni_stats_PowerStates.h"
#include <windows.h>
#include <powrprof.h>
#include <stdio.h> 
#include <stdlib.h> 

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
	system("shutdown /s");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_reboot(JNIEnv*, jclass) {
	system("shutdown /r");
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_stats_PowerStates_logoff(JNIEnv*, jclass) {
	system("shutdown /l");
}