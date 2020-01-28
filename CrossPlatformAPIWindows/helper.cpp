#include "pch.h"

#include <iostream>
#include <sstream>
#include <string>
#include "helper.h"

#include "jni.h"

static bool printErrorOn = FALSE;
static JNIEnv* env;

void printFormat(const wchar_t* format, ...) {
	size_t length = wcslen(format) + 1024;

	va_list args;
	va_start(args, format);

	wchar_t *buff = new wchar_t[length];
	_vsnwprintf_s(buff, length, length - 1, format, args);
	va_end(args);

	std::wstring buffAsStdStr = buff;

	print(buffAsStdStr.c_str());
	delete[] buff;
}

void print(jstring str) {
	if (env == NULL)
		return;

	jclass syscls = env->FindClass("java/lang/System");
	jfieldID fid = env->GetStaticFieldID(syscls, "out", "Ljava/io/PrintStream;");
	jobject out = env->GetStaticObjectField(syscls, fid);
	jclass pscls = env->FindClass("java/io/PrintStream");
	jmethodID mid = env->GetMethodID(pscls, "print", "(Ljava/lang/String;)V");
	env->CallVoidMethod(out, mid, str);
}

void println(jstring str) {
	if (env == NULL)
		return;

	jclass syscls = env->FindClass("java/lang/System");
	jfieldID fid = env->GetStaticFieldID(syscls, "out", "Ljava/io/PrintStream;");
	jobject out = env->GetStaticObjectField(syscls, fid);
	jclass pscls = env->FindClass("java/io/PrintStream");
	jmethodID mid = env->GetMethodID(pscls, "println", "(Ljava/lang/String;)V");
	env->CallVoidMethod(out, mid, str);
}


void print(const char* buf) {
	if (env == NULL) {
		std::wcout << buf << std::endl;
	} else {
		jstring str = env->NewString((jchar*)buf, strlen(buf));
		print(str);
	}
}

void print(const wchar_t *buf) {
	if (env == NULL) {
		std::wcout << buf << std::endl;
	} else {
		jstring str = env->NewString((jchar*)buf, wcslen(buf));
		print(str);
	}
}

void printError() {
	if (!printErrorOn)
		return;

	wchar_t buf[256];
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
	print(buf);
}

void printError(std::string value) {
	if (!printErrorOn)
		return;

	print(value.c_str());
}

void printError(std::wstring value) {
	if (!printErrorOn)
		return;

	print(value.c_str());
}

void setPrintError(JNIEnv* en, bool value) {
	env = en;
	printErrorOn = value;
}

bool isFlagSet(long long word, long long flag) {
	return (word | flag) == flag;
}