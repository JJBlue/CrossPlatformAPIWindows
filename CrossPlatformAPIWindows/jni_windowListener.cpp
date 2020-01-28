#include "pch.h"

#include "crossplatformapi_jni_window_NativeWindowListener.h"
#include "windowListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindowListener_register(JNIEnv* env, jclass) {
    registerWindowListener(env);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_NativeWindowListener_unregister(JNIEnv*, jclass) {
    unregisterWindowListener();
}