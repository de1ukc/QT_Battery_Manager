#include "battery_manager.h"


batteryManager::batteryManager()
{

}

void batteryManager::initChemistry(){}

void batteryManager::fill_infrormation(){
    CallNtPowerInformation(SystemBatteryState, NULL, 0, &this->information, sizeof(this->information));
}
