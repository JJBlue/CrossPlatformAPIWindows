#include "pch.h"

#include "window.h"

#include "jni.h"
#include <iostream>
#include <fstream>
#include <string>

static HHOOK windowHook = NULL;
static bool hooking;

static void CALLBACK Wineventproc(HWINEVENTHOOK hook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
    //TODO Open Close Window
    switch (event) {
        case EVENT_SYSTEM_MINIMIZESTART:
            std::cout << "EVENT_SYSTEM_MINIMIZESTART " << hwnd << std::endl;
            break;
        case EVENT_SYSTEM_MINIMIZEEND:
            std::cout << "EVENT_SYSTEM_MINIMIZEEND " << hwnd << std::endl;
            break;
        case EVENT_SYSTEM_MOVESIZESTART:
            std::cout << "EVENT_SYSTEM_MOVESIZESTART " << hwnd << std::endl;
            break;
        case EVENT_SYSTEM_MOVESIZEEND:
            std::cout << "EVENT_SYSTEM_MOVESIZEEND " << hwnd << std::endl;
            break;
        case EVENT_SYSTEM_FOREGROUND:
            std::cout << "EVENT_SYSTEM_FOREGROUND " << hwnd << std::endl;
            break;
        case EVENT_SYSTEM_DESKTOPSWITCH:
            std::cout << "EVENT_SYSTEM_DESKTOPSWITCH " << hwnd << std::endl;
            break;
        case EVENT_OBJECT_DESTROY:
            if (idObject == OBJID_WINDOW && idChild == INDEXID_CONTAINER) {
                std::cout << "EVENT_OBJECT_DESTROY " << hwnd << std::endl;
            }
            break;
        case EVENT_OBJECT_CREATE:
            if (idObject == OBJID_WINDOW && idChild == INDEXID_CONTAINER) {
                std::cout << "EVENT_OBJECT_CREATE " << hwnd << std::endl;
            }
            break;
        case EVENT_OBJECT_FOCUS:
            std::cout << "EVENT_OBJECT_FOCUS " << hwnd << std::endl;
            break;
    }
}

void registerWindowListener() {
    SetWinEventHook(EVENT_MIN, EVENT_MAX, GetModuleHandle(NULL), Wineventproc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void unregisterWindowListener() {
    hooking = false;
}