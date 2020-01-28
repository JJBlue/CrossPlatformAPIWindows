#include "pch.h"

#include "network.h"
#include "helper.h"

//#include <netlistmgr.h>
#include <Sensapi.h>
#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <vector>

#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "Sensapi.lib")

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

static void printInformation() {
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;
    int iRet = 0;

    WCHAR GuidString[39] = { 0 };

    unsigned int i, j, k;

    /* variables used for WlanEnumInterfaces  */

    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    PWLAN_INTERFACE_INFO pIfInfo = NULL;

    PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
    PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

    int iRSSI = 0;

    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) {
        print(L"WlanOpenHandle failed");
        return;
    }

    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        print(L"WlanEnumInterfaces failed");
        return;
    } else {
        printFormat(L"Num Entries: %lu\n", pIfList->dwNumberOfItems);
        printFormat(L"Current Index: %lu\n", pIfList->dwIndex);
        for (i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
            pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];
            printFormat(L"  Interface Index[%u]:\t %lu\n", i, i);
            iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)&GuidString, sizeof(GuidString) / sizeof(*GuidString));

            if (iRet == 0) {
                print(L"StringFromGUID2 failed\n");
            } else {
                printFormat(L"  InterfaceGUID[%d]: %ws\n", i, GuidString);
            }

            printFormat(L"  Interface Description[%d]: %ws", i, pIfInfo->strInterfaceDescription);
            print(L"\n");
            printFormat(L"  Interface State[%d]:\t ", i);
            
            switch (pIfInfo->isState) {
                case wlan_interface_state_not_ready:
                    print(L"Not ready\n");
                    break;
                case wlan_interface_state_connected:
                    print(L"Connected\n");
                    break;
                case wlan_interface_state_ad_hoc_network_formed:
                    print(L"First node in a ad hoc network\n");
                    break;
                case wlan_interface_state_disconnecting:
                    print(L"Disconnecting\n");
                    break;
                case wlan_interface_state_disconnected:
                    print(L"Not connected\n");
                    break;
                case wlan_interface_state_associating:
                    print(L"Attempting to associate with a network\n");
                    break;
                case wlan_interface_state_discovering:
                    print(L"Auto configuration is discovering settings for the network\n");
                    break;
                case wlan_interface_state_authenticating:
                    print(L"In process of authenticating\n");
                    break;
                default:
                    printFormat(L"Unknown state %ld\n", pIfInfo->isState);
                    break;
            }

            print(L"\n");

            dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid, 0, NULL, &pBssList);

            if (dwResult != ERROR_SUCCESS) {
                printFormat(L"WlanGetAvailableNetworkList failed with error: %u\n", dwResult);
            } else {
                print(L"WLAN_AVAILABLE_NETWORK_LIST for this interface\n");
                printFormat(L"  Num Entries: %lu\n\n", pBssList->dwNumberOfItems);

                for (j = 0; j < pBssList->dwNumberOfItems; j++) {
                    pBssEntry = (WLAN_AVAILABLE_NETWORK*)&pBssList->Network[j];

                    printFormat(L"  Profile Name[%u]:  %ws\n", j, pBssEntry->strProfileName);
                    printFormat(L"  SSID[%u]:\t\t ", j);

                    if (pBssEntry->dot11Ssid.uSSIDLength == 0) {
                        print(L"\n");
                    } else {
                        for (k = 0; k < pBssEntry->dot11Ssid.uSSIDLength; k++) {
                            printFormat(L"%c", (int)pBssEntry->dot11Ssid.ucSSID[k]);
                        }
                        print(L"\n");
                    }

                    printFormat(L"  BSS Network type[%u]:\t ", j);

                    switch (pBssEntry->dot11BssType) {
                        case dot11_BSS_type_infrastructure:
                            printFormat(L"Infrastructure (%u)\n", pBssEntry->dot11BssType);
                            break;
                        case dot11_BSS_type_independent:
                            printFormat(L"Infrastructure (%u)\n", pBssEntry->dot11BssType);
                            break;
                        default:
                            printFormat(L"Other (%lu)\n", pBssEntry->dot11BssType);
                            break;
                    }

                    printFormat(L"  Number of BSSIDs[%u]:\t %u\n", j, pBssEntry->uNumberOfBssids);
                    printFormat(L"  Connectable[%u]:\t ", j);

                    if (pBssEntry->bNetworkConnectable) {
                        print(L"Yes\n");
                    } else {
                        print(L"No\n");
                        printFormat(L"  Not connectable WLAN_REASON_CODE value[%u]:\t %u\n", j, pBssEntry->wlanNotConnectableReason);
                    }

                    printFormat(L"  Number of PHY types supported[%u]:\t %u\n", j, pBssEntry->uNumberOfPhyTypes);

                    if (pBssEntry->wlanSignalQuality == 0)
                        iRSSI = -100;
                    else if (pBssEntry->wlanSignalQuality == 100)
                        iRSSI = -50;
                    else
                        iRSSI = -100 + (pBssEntry->wlanSignalQuality / 2);

                    printFormat(L"  Signal Quality[%u]:\t %u (RSSI: %i dBm)\n", j, pBssEntry->wlanSignalQuality, iRSSI);
                    printFormat(L"  Security Enabled[%u]:\t ", j);
                    print(pBssEntry->bSecurityEnabled ? L"Yes\n" : L"No\n");

                    printFormat(L"  Default AuthAlgorithm[%u]: ", j);
                    switch (pBssEntry->dot11DefaultAuthAlgorithm) {
                        case DOT11_AUTH_ALGO_80211_OPEN:
                            printFormat(L"802.11 Open (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        case DOT11_AUTH_ALGO_80211_SHARED_KEY:
                            printFormat(L"802.11 Shared (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        case DOT11_AUTH_ALGO_WPA:
                            printFormat(L"WPA (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        case DOT11_AUTH_ALGO_WPA_PSK:
                            printFormat(L"WPA-PSK (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        case DOT11_AUTH_ALGO_WPA_NONE:
                            printFormat(L"WPA-None (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        case DOT11_AUTH_ALGO_RSNA:
                            printFormat(L"RSNA (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        case DOT11_AUTH_ALGO_RSNA_PSK:
                            printFormat(L"RSNA with PSK(%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                        default:
                            printFormat(L"Other (%lu)\n", pBssEntry->dot11DefaultAuthAlgorithm);
                            break;
                    }

                    printFormat(L"  Default CipherAlgorithm[%u]: ", j);
                    switch (pBssEntry->dot11DefaultCipherAlgorithm) {
                        case DOT11_CIPHER_ALGO_NONE:
                            printFormat(L"None (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                        case DOT11_CIPHER_ALGO_WEP40:
                            printFormat(L"WEP-40 (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                        case DOT11_CIPHER_ALGO_TKIP:
                            printFormat(L"TKIP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                        case DOT11_CIPHER_ALGO_CCMP:
                            printFormat(L"CCMP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                        case DOT11_CIPHER_ALGO_WEP104:
                            printFormat(L"WEP-104 (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                        case DOT11_CIPHER_ALGO_WEP:
                            printFormat(L"WEP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                        default:
                            printFormat(L"Other (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
                            break;
                    }

                    printFormat(L"  Flags[%u]:\t 0x%x", j, pBssEntry->dwFlags);
                    
                    if (pBssEntry->dwFlags) {
                        if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)
                            print(L" - Currently connected");
                        if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_HAS_PROFILE)
                            print(L" - Has profile");
                    }

                    print(L"\n\n");
                }
            }
        }
    }

    if (pBssList != NULL) {
        WlanFreeMemory(pBssList);
        pBssList = NULL;
    }

    if (pIfList != NULL) {
        WlanFreeMemory(pIfList);
        pIfList = NULL;
    }
}

void getCurrentSSIDs(std::vector<std::wstring>* connectedSSID, std::vector<std::wstring>* SSIDs) {
    if (connectedSSID == NULL && SSIDs == NULL)
        return;

    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;

    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    PWLAN_INTERFACE_INFO pIfInfo = NULL;

    PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
    PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) {
        return;
    }

    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        return;
    } else {
        for (unsigned int i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
            pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];

            dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid, 0, NULL, &pBssList);

            switch (pIfInfo->isState) {
                case wlan_interface_state_connected:
                    break;
                default:
                    if (SSIDs == NULL)
                        continue;
            }

            if (dwResult != ERROR_SUCCESS) {
                continue;
            } else {
                for (unsigned int j = 0; j < pBssList->dwNumberOfItems; j++) {
                    pBssEntry = (WLAN_AVAILABLE_NETWORK*)&pBssList->Network[j];

                    std::wstring ssid;

                    if (pBssEntry->dot11Ssid.uSSIDLength == 0) {
                        continue;
                    } else {
                        for (unsigned int k = 0; k < pBssEntry->dot11Ssid.uSSIDLength; k++) {
                            ssid.push_back((int)pBssEntry->dot11Ssid.ucSSID[k]);
                        }
                    }

                    if (SSIDs != NULL) {
                        SSIDs->push_back(ssid);
                    }

                    if (connectedSSID != NULL && pBssEntry->dwFlags && pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED) {
                        connectedSSID->push_back(ssid);
                    }
                }
            }
        }
    }

    if (pBssList != NULL) {
        WlanFreeMemory(pBssList);
        pBssList = NULL;
    }

    if (pIfList != NULL) {
        WlanFreeMemory(pIfList);
        pIfList = NULL;
    }
}

bool hasInternetAccess() {
	DWORD dwSens;
	return IsNetworkAlive(&dwSens);
}