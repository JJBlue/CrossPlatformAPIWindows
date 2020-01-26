/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class crossplatformapi_jni_display_NativeDisplay */

#ifndef _Included_crossplatformapi_jni_display_NativeDisplay
#define _Included_crossplatformapi_jni_display_NativeDisplay
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getPrimaryDisplay
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getPrimaryDisplay
  (JNIEnv *, jclass);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getDisplay
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getDisplay__J
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getDisplay
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getDisplay__JJ
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getDisplays
 * Signature: ()[J
 */
JNIEXPORT jlongArray JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getDisplays
  (JNIEnv *, jclass);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    isPrimary
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_display_NativeDisplay_isPrimary
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getX
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getX
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getY
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getY
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getWidth
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWidth
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getHeight
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getHeight
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getWorkX
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkX
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getWorkY
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkY
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getWorkWidth
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkWidth
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getWorkHeight
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getWorkHeight
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    setBrightness
 * Signature: (J)J
 */
JNIEXPORT void JNICALL Java_crossplatformapi_jni_display_NativeDisplay_setBrightness
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getBrightness
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getBrightness
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getMinBrightness
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getMinBrightness
  (JNIEnv *, jclass, jlong);

/*
 * Class:     crossplatformapi_jni_display_NativeDisplay
 * Method:    getMaxBrightness
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_crossplatformapi_jni_display_NativeDisplay_getMaxBrightness
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
