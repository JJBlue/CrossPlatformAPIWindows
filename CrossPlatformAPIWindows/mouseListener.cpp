#include "pch.h"

#include "crossplatformapi_jni_mouse_NativeMouseListener.h"

#include <windowsx.h>

static volatile bool hooking = false;
static bool block = false;
static HHOOK mouseHook;

static JNIEnv* envi;
static jclass clazz;
static jmethodID m_move, m_scroll, m_hscroll, m_press, m_release;

#include<iostream>

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    //PMSLLHOOKSTRUCT info = (PMSLLHOOKSTRUCT)lParam;
    switch (wParam) {
        case WM_LBUTTONDOWN:
            envi->CallStaticVoidMethod(clazz, m_press, VK_LBUTTON);
            break;
        case WM_LBUTTONUP:
            envi->CallStaticVoidMethod(clazz, m_release, VK_LBUTTON);
            break;
        case WM_RBUTTONDOWN:
            envi->CallStaticVoidMethod(clazz, m_press, VK_RBUTTON);
            break;
        case WM_RBUTTONUP:
            envi->CallStaticVoidMethod(clazz, m_release, VK_RBUTTON);
            break;
        case WM_MBUTTONDOWN:
            envi->CallStaticVoidMethod(clazz, m_press, VK_MBUTTON);
            break;
        case WM_MBUTTONUP:
            envi->CallStaticVoidMethod(clazz, m_release, VK_MBUTTON);
            break;
        case WM_XBUTTONDOWN: {
            PMSLLHOOKSTRUCT info = (PMSLLHOOKSTRUCT)lParam;
            int xbutton = GET_XBUTTON_WPARAM(info->mouseData);
            envi->CallStaticVoidMethod(clazz, m_press, VK_XBUTTON1 - 1 + xbutton);
            break;
        }
        case WM_XBUTTONUP: {
            PMSLLHOOKSTRUCT info = (PMSLLHOOKSTRUCT)lParam;
            int xbutton = GET_XBUTTON_WPARAM(info->mouseData);
            envi->CallStaticVoidMethod(clazz, m_release, VK_XBUTTON1 - 1 + xbutton);
            break;
        }
        case WM_MOUSEMOVE:
            envi->CallStaticVoidMethod(clazz, m_move, (long) GET_X_LPARAM(lParam), (long) GET_Y_LPARAM(lParam));
            break;
        case WM_MOUSEWHEEL: {
            PMSLLHOOKSTRUCT info = (PMSLLHOOKSTRUCT)lParam;
            envi->CallStaticVoidMethod(clazz, m_scroll, (jlong)(jshort) GET_WHEEL_DELTA_WPARAM(info->mouseData));
            break;
        }
        case WM_MOUSEHWHEEL: {
            PMSLLHOOKSTRUCT info = (PMSLLHOOKSTRUCT)lParam;
            envi->CallStaticVoidMethod(clazz, m_hscroll, (jlong)(jshort) GET_WHEEL_DELTA_WPARAM(info->mouseData));
            break;
        }
    }
    auto value = CallNextHookEx(NULL, nCode, wParam, lParam);
    return block ? 1 : value;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouseListener_register(JNIEnv* env, jclass){
    hooking = true;
    envi = env;
    clazz = envi->FindClass("crossplatformapi/main/mouse/MouseEventReceiver");
    
    m_move = envi->GetStaticMethodID(clazz, "move", "(JJ)V");
    m_scroll = envi->GetStaticMethodID(clazz, "scroll", "(J)V");
    m_hscroll = envi->GetStaticMethodID(clazz, "hscroll", "(J)V");
    m_press = envi->GetStaticMethodID(clazz, "press", "(I)V");
    m_release = envi->GetStaticMethodID(clazz, "release", "(I)V");

    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) && hooking) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
    mouseHook = NULL;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouseListener_unregister(JNIEnv*, jclass) {
    hooking = false;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouseListener_block(JNIEnv*, jclass) {
    block = true;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_NativeMouseListener_unblock(JNIEnv*, jclass) {
    block = false;
}