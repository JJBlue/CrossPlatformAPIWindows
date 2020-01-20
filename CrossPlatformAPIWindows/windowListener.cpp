#include "pch.h"

#include "window.h"
#include "jni.h"

#include <iostream>

static HHOOK windowHook = NULL;
static volatile bool hooking;

static JNIEnv* envi;
static jclass clazz;
static jmethodID maximized, minimized, restore, move, resize, foreground;

static void CALLBACK Wineventproc(HWINEVENTHOOK hook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {

    if (hwnd == NULL)
        return;

    if (!isUserWindow(hwnd)) {
        return;
    }

    //TODO Open Close Window
    switch (event) {
        //case EVENT_SYSTEM_MINIMIZESTART:
        //case EVENT_SYSTEM_MINIMIZEEND:
        //case EVENT_SYSTEM_MOVESIZESTART:
        //case EVENT_SYSTEM_MOVESIZEEND:
        //    envi->CallStaticVoidMethod(clazz, move, hwndToLong(hwnd));
        //    envi->CallStaticVoidMethod(clazz, resize, hwndToLong(hwnd));
        //    break;
        //case EVENT_OBJECT_FOCUS:
        //    std::cout << "EVENT_OBJECT_FOCUS " << hwnd << std::endl;
        //    break;
        case EVENT_SYSTEM_FOREGROUND:
            envi->CallStaticVoidMethod(clazz, foreground, hwndToLong(hwnd));
            break;
        case EVENT_SYSTEM_DESKTOPSWITCH:
            std::cout << "EVENT_SYSTEM_DESKTOPSWITCH " << hwnd << std::endl;
            break;
        case EVENT_OBJECT_DESTROY:
            if (isUserWindow(hwnd)) {
                std::cout << "EVENT_OBJECT_DESTROY " << hwnd << std::endl;
            }
            break;
        case EVENT_OBJECT_CREATE:
            if (isUserWindow(hwnd)) {
                std::cout << "EVENT_OBJECT_CREATE " << hwnd << std::endl;
            }
            break;
        case EVENT_OBJECT_LOCATIONCHANGE:
            WINDOWPLACEMENT wp;
            wp.length = sizeof(WINDOWPLACEMENT);
            GetWindowPlacement(hwnd, &wp);

            switch (wp.showCmd) {
                case SW_SHOWNORMAL: //restore, move and resize
                    //std::cout << "EVENT_OBJECT_LOCATIONCHANGE " << "normal" << std::endl;
                    envi->CallStaticVoidMethod(clazz, restore, hwndToLong(hwnd));
                    envi->CallStaticVoidMethod(clazz, move, hwndToLong(hwnd));
                    envi->CallStaticVoidMethod(clazz, resize, hwndToLong(hwnd));
                    break;
                case SW_SHOWMAXIMIZED:
                    envi->CallStaticVoidMethod(clazz, maximized, hwndToLong(hwnd));
                    break;
                case SW_SHOWMINIMIZED:
                    envi->CallStaticVoidMethod(clazz, minimized, hwndToLong(hwnd));
                    break;
                default:
                    std::cout << "EVENT_OBJECT_LOCATIONCHANGE " << wp.showCmd << std::endl;
            }

            break;
    }
}

void registerWindowListener(JNIEnv* env) {
    if (hooking) return;

    hooking = true;
    envi = env;
    clazz = envi->FindClass("crossplatformapi/main/window/WindowEventReceiver");

    maximized = envi->GetStaticMethodID(clazz, "maximized", "(J)V");
    minimized = envi->GetStaticMethodID(clazz, "minimized", "(J)V");
    restore = envi->GetStaticMethodID(clazz, "restore", "(J)V");
    move = envi->GetStaticMethodID(clazz, "move", "(J)V");
    resize = envi->GetStaticMethodID(clazz, "resize", "(J)V");
    foreground = envi->GetStaticMethodID(clazz, "foregroundChanged", "(J)V");

    HWINEVENTHOOK hook = SetWinEventHook(EVENT_MIN, EVENT_MAX, GetModuleHandle(NULL), Wineventproc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) && hooking) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWinEvent(hook);
}

void unregisterWindowListener() {
    hooking = false;
}