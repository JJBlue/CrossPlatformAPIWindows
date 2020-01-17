#include "pch.h"

#include "crossplatformapi_jni_window_WindowListener.h"
#include "windowListener.h"

JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_WindowListener_registerListener(JNIEnv*, jclass) {
    registerWindowListener();
}

/*
 * Class:     crossplatformapi_jni_window_WindowListener
 * Method:    unrigsterListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_window_WindowListener_unregisterListener(JNIEnv*, jclass) {
    unregisterWindowListener();
}