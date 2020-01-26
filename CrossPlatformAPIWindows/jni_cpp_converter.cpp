#include "pch.h"

#include "jni.h"
#include <string>

jstring stringToJString(std::string s, JNIEnv* env) {
	return env->NewString((const jchar*)s.c_str(), s.length());
}

jstring wstringToJString(std::wstring s, JNIEnv* env) {
	return env->NewString((const jchar*) s.c_str(), s.length());
}