#pragma once

#include <string>
#include "jni.h"

void printFormat(const wchar_t* format, ...);

void printError();
void printError(std::string);
void printError(std::wstring);
void print(jstring str);
void print(const char* buf);
void print(const wchar_t* buf);

void setPrintError(JNIEnv*, bool);

bool isFlagSet(long long word, long long flag);