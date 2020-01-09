#include "pch.h"

#include "crossplatformapi_jni_mouse_MouseListener.h"

HHOOK mouseHook;

JNIEnv* envi;
jclass clazz;
jmethodID methodHookMouse;

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    //wParam = WM_LBUTTONDOWN, WM_LBUTTONUP, WM_MOUSEMOVE, WM_MOUSEWHEEL, WM_MOUSEHWHEEL, WM_RBUTTONDOWN, or WM_RBUTTONUP
    
    PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT) lParam;
    //mouseData: 0x0001 MouseButton one, 0x0002 MouseButton two
    //pt: x,y


//    position.x = p->pt.x;
//    position.y = p->pt.y;
    envi->CallStaticVoidMethod(clazz, methodHookMouse, (int) wParam, (int)key->vkCode, (int)key->flags);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}



JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_MouseListener_registerListener(JNIEnv*, jclass) {


    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, NULL, NULL);
}

JNIEXPORT void JNICALL Java_crossplatformapi_jni_mouse_MouseListener_unregisterListener(JNIEnv*, jclass) {
    if (mouseHook != NULL) {
        UnhookWindowsHookEx(mouseHook);
        mouseHook = NULL;
    }
}