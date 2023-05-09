#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include <iostream>
#include <Windows.h> // UCHAR
#include <Powerbase.h>
#include <QString>
#include <winbase.h>

#pragma comment (lib, "setupapi.lib") // for Chemistry

#include <Poclass.h>
#include <Setupapi.h>
#include <devguid.h>

#pragma comment(lib, "PowrProf.lib")
extern "C" {
#include <Powrprof.h>

}

#include "batclass.h"


class batteryManager
{
private:
    UCHAR chemistry[4] = { "0" };
    SYSTEM_POWER_STATUS battery;
    SYSTEM_BATTERY_STATE information;
    BATTERY_INFORMATION BatteryInfo;

    ULONG DesignedCapacity;
    ULONG CycleCount;

public:
    batteryManager();

    void initChemistry();
    void fillInfrormation();
    bool fillBattery();
    void fillChemistry();
    void sleep();
    void hibernation();
 //   void set_battery_saver();

    QString getACStatus();
    QString getBatteryChargeProcent();
    QString getBatteryType();
    QString getCurrentCapacity();
    QString getMaxCapacity();
    QString getDesignedCapacity();
    QString getCyclesCount();
    QString getBatteryLifetime();
    QString getBatteryRemaninChargeTime();
    QString getBatterySaverStatus();
    std::string getChargeSpeed();

    int getBatteryProcent();
    int getMaxCapacityInt();
    int getCurrentCapacityInt();
    long getRate();

    bool charging();
    bool discharging();
    bool isBatteryInSystem();

};


#endif // BATTERY_MANAGER_H


// SYSTEM_POWER_STATUS https://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-system_power_status
// SYSTEM_BATTERY_STATE https://github.com/MicrosoftDocs/sdk-api/blob/docs/sdk-api-src/content/winnt/ns-winnt-system_battery_state.md
