#include "pch.h"

#include "batteryListener.h"
#include "jni.h"
#include "helper.h"

static HPOWERNOTIFY powerSchemeNotify, powerSourceNotify, batteryPowerNotify;

static DWORD handlerFunctionEx(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext) {
    
}

void registerPowerListener(JNIEnv* env) {
	if (powerSchemeNotify != NULL)
		return;

	GUID guid;

	powerSchemeNotify = RegisterPowerSettingNotification(NULL, &GUID_POWERSCHEME_PERSONALITY, DEVICE_NOTIFY_SERVICE_HANDLE);
	powerSourceNotify = RegisterPowerSettingNotification(NULL, &GUID_ACDC_POWER_SOURCE, DEVICE_NOTIFY_SERVICE_HANDLE);
	batteryPowerNotify = RegisterPowerSettingNotification(NULL, &GUID_BATTERY_PERCENTAGE_REMAINING, DEVICE_NOTIFY_SERVICE_HANDLE);

	if(powerSchemeNotify == NULL) {
		printError();
	}
}

void unregisterPowerListener(JNIEnv* env) {
	if (powerSchemeNotify == NULL)
		return;

	UnregisterPowerSettingNotification(powerSchemeNotify);
	UnregisterPowerSettingNotification(powerSourceNotify);
	UnregisterPowerSettingNotification(batteryPowerNotify);

	powerSchemeNotify = NULL;
}