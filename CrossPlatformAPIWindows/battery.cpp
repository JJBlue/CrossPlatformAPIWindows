#include "pch.h"

#include "helper.h"
#include <iostream>

long getCurrentBatteryInPercent() {
	SYSTEM_POWER_STATUS status;
	if (!GetSystemPowerStatus(&status)) {
		printError();
		return -1;
	}

	return status.BatteryLifePercent;
}

bool isCharging() {
	SYSTEM_POWER_STATUS status;
	if (!GetSystemPowerStatus(&status)) {
		printError();
		return FALSE;
	}

	return isFlagSet(status.ACLineStatus, AC_LINE_ONLINE);
}

bool isBatterySaverOn() {
	SYSTEM_POWER_STATUS status;
	if (!GetSystemPowerStatus(&status)) {
		printError();
		return FALSE;
	}

	return isFlagSet(status.SystemStatusFlag, SYSTEM_STATUS_FLAG_POWER_SAVING_ON);
}