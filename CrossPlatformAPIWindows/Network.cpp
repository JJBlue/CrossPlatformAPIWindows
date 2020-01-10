#include "pch.h"

#include "crossplatformapi_jni_network_Network.h"

//#include <netlistmgr.h>
#include <Sensapi.h>

#pragma comment(lib, "Sensapi.lib")

JNIEXPORT jboolean JNICALL Java_crossplatformapi_jni_network_Network_isConnected(JNIEnv*, jclass) {
	DWORD dwSens;
	return IsNetworkAlive(&dwSens);
}
