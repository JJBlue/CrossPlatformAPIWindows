#pragma once

extern JNIEnv* envi;
extern jclass keyboardReceiverClass;
extern jmethodID m_keyPress, m_keyRelease, m_keyHotKey;

void setKeyHooking(bool value);

void setKeyBlock(bool value);

void startKeyHooking();