#include "pch.h"

#include "batteryListener.h"
#include "jni.h"
#include "helper.h"

#include <powersetting.h>
#include <powrprof.h>

#include <iostream>

static HPOWERNOTIFY powerNotify, acdcPowerNotify, batterySaverNotify;

static JavaVM* jvm;
static JNIEnv* env;
static jclass batteryClass;
static jmethodID batteryRemaining, acPower, batteryPower, shortTermPower, batterySaver;

static void init() {
	jvm->AttachCurrentThread((void**)&env, NULL);
	batteryClass = env->FindClass("crossplatformapi/main/battery/BatteryReceiver");
	batteryRemaining = env->GetStaticMethodID(batteryClass, "percentRemainingBattery", "(J)V");

	acPower = env->GetStaticMethodID(batteryClass, "powerplug", "()V");
	batteryPower = env->GetStaticMethodID(batteryClass, "batteryPower", "()V");
	shortTermPower = env->GetStaticMethodID(batteryClass, "short_term_Power", "()V");
	batterySaver = env->GetStaticMethodID(batteryClass, "batterySaverChanged", "(Z)V");
}

static void deinit() {
	jvm->DetachCurrentThread();
}

static ULONG CALLBACK DeviceNotifyCallbackRoutine(PVOID context, ULONG type, PVOID setting) {
	POWERBROADCAST_SETTING *powersetting = (POWERBROADCAST_SETTING*)setting;

	init();

	if (powersetting->PowerSetting == GUID_BATTERY_PERCENTAGE_REMAINING) {
		DWORD value = powersetting->Data[0];
		env->CallStaticVoidMethod(batteryClass, batteryRemaining, (jlong) value);
	} else if(powersetting->PowerSetting == GUID_ACDC_POWER_SOURCE) {
		DWORD value = powersetting->Data[0];
	
		switch (value) {
			case PoAc: //plug in
				env->CallStaticVoidMethod(batteryClass, acPower);
				break;
			case PoDc: //battery
				env->CallStaticVoidMethod(batteryClass, batteryPower);
				break;
			case PoHot: //short-term power source
				env->CallStaticVoidMethod(batteryClass, shortTermPower);
				break;
		}
	} else if (powersetting->PowerSetting == GUID_POWER_SAVING_STATUS) {
		DWORD value = powersetting->Data[0];

		if (value == 0x0) { //Battery saver off
			env->CallStaticVoidMethod(batteryClass, batterySaver, (jboolean) false);
		} else if (value == 0x1) { //Battery saver on
			env->CallStaticVoidMethod(batteryClass, batterySaver, (jboolean) true);
		}
	}

	deinit();

	return 0;
}

static void registerListener(LPCGUID guid, PHPOWERNOTIFY notify) {
	if (guid == NULL || *notify != NULL || notify == NULL) return;

	DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS recipient;
	recipient.Callback = DeviceNotifyCallbackRoutine;
	recipient.Context = NULL;

	if (PowerSettingRegisterNotification(guid, DEVICE_NOTIFY_CALLBACK, &recipient, notify) != 0) {
		print(L"Some Battery Listeners couldn't be register");
	}
}

void registerPowerListener(JNIEnv* envi) {
	if (envi == NULL) return;

	envi->GetJavaVM(&jvm);

	registerListener(&GUID_BATTERY_PERCENTAGE_REMAINING, &powerNotify);
	registerListener(&GUID_ACDC_POWER_SOURCE, &acdcPowerNotify);
	registerListener(&GUID_POWER_SAVING_STATUS, &batterySaverNotify);
}

static void unregister(PHPOWERNOTIFY notify) {
	if (*notify == NULL)
		return;

	PowerSettingUnregisterNotification(*notify);
	*notify = NULL;
}

void unregisterPowerListener(JNIEnv* env) {
	unregister(&powerNotify);
	unregister(&acdcPowerNotify);
	unregister(&batterySaverNotify);
}