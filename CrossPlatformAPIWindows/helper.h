#pragma once

#include <string>
#include "jni.h"

void printError();
void printError(std::string);
void printError(std::wstring);

void setPrintError(JNIEnv*, bool);

bool isFlagSet(long long word, long long flag);