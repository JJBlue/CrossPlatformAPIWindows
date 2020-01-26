#pragma once

#include "jni.h"
#include <string>

jstring stringToJString(std::string s, JNIEnv* env);

jstring wstringToJString(std::wstring s, JNIEnv* env);