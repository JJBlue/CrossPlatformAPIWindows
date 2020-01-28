#pragma once

#include <vector>
#include <string>

void getCurrentSSIDs(std::vector<std::wstring>* connectedSSID, std::vector<std::wstring>* SSIDs);
bool hasInternetAccess();