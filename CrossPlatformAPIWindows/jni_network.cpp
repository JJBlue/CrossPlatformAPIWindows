#include "pch.h"

#include "crossplatformapi_jni_network_Network.h"
#include "network.h"
#include "helper.h"
#include "jni_cpp_converter.h"

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_network_Network_isConnected(JNIEnv*, jclass) {
	return hasInternetAccess();
}

JNIEXPORT jobjectArray JNICALL Java_crossplatformapi_jni_network_Network_getConnectedSSIDs(JNIEnv* env, jclass) {
	std::vector<std::wstring> connected;
	getCurrentSSIDs(&connected, NULL);

	jobjectArray objectArray = env->NewObjectArray(connected.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));

	int count = 0;
	for (std::wstring s : connected) {
		env->SetObjectArrayElement(objectArray, count, wstringToJString(s, env));
		count++;
	}

	return objectArray;
}

JNIEXPORT jobjectArray JNICALL Java_crossplatformapi_jni_network_Network_getAllSSIDs(JNIEnv* env, jclass) {
	std::vector<std::wstring> ssids;
	getCurrentSSIDs(NULL, &ssids);

	jobjectArray objectArray = env->NewObjectArray(ssids.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));

	int count = 0;
	for (std::wstring s : ssids) {
		env->SetObjectArrayElement(objectArray, count, wstringToJString(s, env));
		count++;
	}

	return objectArray;
}