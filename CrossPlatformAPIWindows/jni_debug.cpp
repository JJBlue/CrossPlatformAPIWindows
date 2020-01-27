#include "pch.h"

#include "crossplatformapi_jni_debug_NativeDebug.h"
#include "helper.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_debug_NativeDebug_printError(JNIEnv* env, jclass, jboolean value) {
	setPrintError(env, value);
}