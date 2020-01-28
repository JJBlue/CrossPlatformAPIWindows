#include "pch.h"

#include "batteryListener.h"
#include "jni.h"
#include "helper.h"

#include <powersetting.h>
#include <powrprof.h>

#include <iostream>

static HPOWERNOTIFY powerNotify;

static ULONG CALLBACK DeviceNotifyCallbackRoutine(PVOID context, ULONG type, PVOID setting) {
	POWERBROADCAST_SETTING *powersetting = (POWERBROADCAST_SETTING*)setting;

	std::cout << (DWORD)powersetting->DataLength << " " << (DWORD) powersetting->Data[0] << "\n" << std::endl;

	//printFormat(L"Value: %i", powersetting->Data);

	return 0;
}

void registerPowerListener(JNIEnv* env) {
	if (powerNotify != NULL)
		return;

	DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS recipient;
	recipient.Callback = DeviceNotifyCallbackRoutine;
	recipient.Context = NULL;

	if (PowerSettingRegisterNotification(&GUID_BATTERY_PERCENTAGE_REMAINING, DEVICE_NOTIFY_CALLBACK, &recipient, &powerNotify) != 0) {
		print("Error");
	}
}

void unregisterPowerListener(JNIEnv* env) {
	if (powerNotify == NULL)
		return;

	PowerSettingUnregisterNotification(powerNotify);
	powerNotify = NULL;
}