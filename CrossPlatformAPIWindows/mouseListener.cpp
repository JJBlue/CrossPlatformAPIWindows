#include "pch.h"

#include "crossplatformapi_jni_mouse_MouseListener.h"

#include <windowsx.h>

static bool hooking = false;
static bool block = false;
static HHOOK mouseHook;

static JNIEnv* envi;
static jclass clazz;
static jmethodID m_move, m_scroll, m_press, m_release;

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    //PMSLLHOOKSTRUCT info = (PMSLLHOOKSTRUCT)lParam;
    switch (wParam) {
        case WM_LBUTTONDOWN:
            envi->CallStaticVoidMethod(clazz, m_press, 0);
            break;
        case WM_LBUTTONUP:
            envi->CallStaticVoidMethod(clazz, m_release, 0);
            break;
        case WM_RBUTTONDOWN:
            envi->CallStaticVoidMethod(clazz, m_press, 1);
            break;
        case WM_RBUTTONUP:
            envi->CallStaticVoidMethod(clazz, m_release, 1);
            break;
        case WM_XBUTTONDOWN: {
            int xbutton = GET_XBUTTON_WPARAM(wParam);
            envi->CallStaticVoidMethod(clazz, m_press, xbutton + 2);
            break;
        }
        case WM_XBUTTONUP: {
            int xbutton = GET_XBUTTON_WPARAM(wParam);
            envi->CallStaticVoidMethod(clazz, m_release, xbutton + 2);
            break;
        }
        case WM_MOUSEMOVE:
            envi->CallStaticVoidMethod(clazz, m_move, (long) GET_X_LPARAM(lParam), (long) GET_Y_LPARAM(lParam));
            break;
        case WM_MOUSEWHEEL:
            envi->CallStaticVoidMethod(clazz, m_scroll, (long) GET_WHEEL_DELTA_WPARAM(wParam));
            break;
        case WM_MOUSEHWHEEL:
            break;
    }
    auto value = CallNextHookEx(NULL, nCode, wParam, lParam);
    return block ? 1 : value;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_MouseListener_registerListener(JNIEnv* env, jclass) {
    hooking = true;
    envi = env;
    clazz = envi->FindClass("crossplatformapi/main/mouse/MouseEventReceiver");
    
    m_move = envi->GetStaticMethodID(clazz, "move", "(JJ)V");
    m_scroll = envi->GetStaticMethodID(clazz, "scroll", "(J)V");
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

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_MouseListener_unregisterListener(JNIEnv*, jclass) {
    hooking = false;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_MouseListener_block(JNIEnv*, jclass) {
    block = true;
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_MouseListener_unblock(JNIEnv*, jclass) {
    block = false;
}