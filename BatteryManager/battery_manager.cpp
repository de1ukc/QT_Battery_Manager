#include "battery_manager.h"


batteryManager::batteryManager()
{

}

void batteryManager::initChemistry(){}

void batteryManager::fill_infrormation(){
    CallNtPowerInformation(SystemBatteryState, NULL, 0, &this->information, sizeof(this->information));
}


void batteryManager::sleep(){
    SetSuspendState(false, false, true);
}

void batteryManager::hibernation(){
    SetSuspendState(true, false, false);
}
