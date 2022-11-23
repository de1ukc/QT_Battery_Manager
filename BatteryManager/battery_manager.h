#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include <iostream>
#include <Windows.h> // UCHAR
#include <Powerbase.h>

#pragma comment(lib, "PowrProf.lib")
extern "C" {
#include <Powrprof.h>

}



class batteryManager
{
private:
    UCHAR chemistry[4] = { "0" };
    SYSTEM_POWER_STATUS battery;
    SYSTEM_BATTERY_STATE information;
public:
    batteryManager();

    void initChemistry();
    void fill_infrormation();
    void sleep();
    void hibernation();
};

#endif // BATTERY_MANAGER_H


// SYSTEM_POWER_STATUS https://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-system_power_status
// SYSTEM_BATTERY_STATE https://github.com/MicrosoftDocs/sdk-api/blob/docs/sdk-api-src/content/winnt/ns-winnt-system_battery_state.md
