/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class crossplatformapi_jni_keyboard_NativeKeyboard */

#ifndef _Included_crossplatformapi_jni_keyboard_NativeKeyboard
#define _Included_crossplatformapi_jni_keyboard_NativeKeyboard
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    registerHotKey
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_registerHotKey
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    unregisterHotKey
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_unregisterHotKey
  (JNIEnv *, jclass, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    isKeyPressed
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_isKeyPressed
  (JNIEnv *, jclass, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    press
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_press
  (JNIEnv *, jclass, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    release
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_release
  (JNIEnv *, jclass, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    write
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_write
  (JNIEnv *, jclass, jstring);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    press2
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_press2
  (JNIEnv *, jclass, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    release2
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_release2
  (JNIEnv *, jclass, jint);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    getKeyboardLayout
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_getKeyboardLayout
  (JNIEnv *, jclass);

/*
 * Class:     crossplatformapi_jni_keyboard_NativeKeyboard
 * Method:    getPhysicalLayout
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_crossplatformapi_jni_keyboard_NativeKeyboard_getPhysicalLayout
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
