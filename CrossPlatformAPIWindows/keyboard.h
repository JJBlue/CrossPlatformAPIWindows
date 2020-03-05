#pragma once

#include <string>

void pressKey(int key);
void pressScanKey(int key);

void releaseKey(int key);
void releaseScanKey(int key);

void write(std::wstring text);

bool isKeyPressed(int key);