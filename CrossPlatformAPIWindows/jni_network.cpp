#include "pch.h"

#include "crossplatformapi_jni_network_Network.h"
#include "network.h"
#include "helper.h"

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_network_Network_isConnected(JNIEnv*, jclass) {
	//test();
	return hasInternetAccess();
}
