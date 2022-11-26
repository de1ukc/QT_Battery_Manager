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
    void fill_infrormation();
    bool fill_battery();
    void fill_chemistry();
    void sleep();
    void hibernation();
 //   void set_battery_saver();

    QString get_AC_status();
    QString get_battery_charge_procent();
    QString get_battery_type();
    QString get_current_capacity();
    QString get_max_capacity();
    QString get_designed_capacity();
    QString get_cycles_count();
    QString get_battery_lifetime();
    QString get_battery_full_lifetime();
    QString get_battery_saver_status();
    std::string get_charge_speed();


    bool charging();

};

#endif // BATTERY_MANAGER_H


// SYSTEM_POWER_STATUS https://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-system_power_status
// SYSTEM_BATTERY_STATE https://github.com/MicrosoftDocs/sdk-api/blob/docs/sdk-api-src/content/winnt/ns-winnt-system_battery_state.md
