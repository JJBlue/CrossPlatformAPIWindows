#include "pch.h"

#include "crossplatformapi_jni_process_NativeProcess.h"
#include "processes.h"

JNIEXPORT jlongArray JNICALL Java_crossplatformapi_jni_process_NativeProcess_getProcesses(JNIEnv*, jclass) {
	std::vector<void*> list;
	listAllProcesses(list);
	return NULL;
}