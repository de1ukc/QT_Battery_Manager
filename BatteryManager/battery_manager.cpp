#include "battery_manager.h"



batteryManager::batteryManager()
{

    bool fill_battery_sucsess = fill_battery();
    fill_infrormation();
    initChemistry();

}

void batteryManager::initChemistry(){
    HDEVINFO DeviceInfoSet;
    DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
    DeviceInterfaceData.cbSize = sizeof(SP_DEVINFO_DATA);

    SetupDiEnumDeviceInterfaces(DeviceInfoSet, NULL, &GUID_DEVCLASS_BATTERY, 0, &DeviceInterfaceData);
    DWORD cbRequired = 0;

    SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, NULL, &cbRequired, NULL);
    PSP_DEVICE_INTERFACE_DETAIL_DATA devId = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);
    devId->cbSize = sizeof(*devId);

    SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, devId, cbRequired, &cbRequired, NULL);

    HANDLE hBattery = CreateFile(devId->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    BATTERY_QUERY_INFORMATION BatteryQueryInformation = { 0 };
    DWORD bytesWait = 0;
    DWORD bytesReturned = 0;
    DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_TAG, &bytesWait, sizeof(bytesWait), &BatteryQueryInformation.BatteryTag,
        sizeof(BatteryQueryInformation.BatteryTag), &bytesReturned, NULL) && BatteryQueryInformation.BatteryTag;

    BATTERY_INFORMATION BatteryInfo = { 0 };
    BatteryQueryInformation.InformationLevel = BatteryInformation;


    DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_INFORMATION, &BatteryQueryInformation, sizeof(BatteryQueryInformation),
        &BatteryInfo, sizeof(BatteryInfo), &bytesReturned, NULL);

    for (int b = 0; b < 4; b++) {
        chemistry[b] = BatteryInfo.Chemistry[b];
    };

    this->DesignedCapacity = BatteryInfo.DesignedCapacity;
    this->CycleCount = BatteryInfo.CycleCount;

    LocalFree(devId);
    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}

void batteryManager::fill_infrormation(){
   CallNtPowerInformation(SystemBatteryState, NULL, 0, &this->information, sizeof(this->information));
}

bool batteryManager::fill_battery()
{
    return  GetSystemPowerStatus(&this->battery);
}


void batteryManager::sleep(){
    SetSuspendState(false, false, true);
}

void batteryManager::hibernation(){
    SetSuspendState(true, false, false);
}

//void batteryManager::set_battery_saver()
//{
//    this->battery.SystemStatusFlag = 1;
//}

QString batteryManager::get_AC_status()
{
    if (this->battery.ACLineStatus == 1) {
        return "От сети";
    } else if (this->battery.ACLineStatus == 0){
        return "От батареи";
    } else {
        return "Статус неизвестен";
    }
}

QString batteryManager::get_battery_charge_procent(){
    int battery_life_percent = this->battery.BatteryLifePercent;
    return QString::number(battery_life_percent);
}

QString batteryManager::get_battery_type()
{
    char a[4];

    for (int b = 0; b < 4; b++)
    {
        a[b] = this->chemistry[b];
    }

    QString battery_type = QString::fromUtf8(a);
    return battery_type;
}

QString batteryManager::get_current_capacity()
{
    QString capacity = QString::number(this->information.RemainingCapacity);
    return capacity;
}

QString batteryManager::get_max_capacity()
{
    QString capacity = QString::number(this->information.MaxCapacity);
    return capacity;
}

QString batteryManager::get_designed_capacity()
{
    QString capacity = QString::number(this->DesignedCapacity);
    return capacity;
}

QString batteryManager::get_cycles_count(){
    if (this->CycleCount == 0){
        return "Батарея не имеет счётчика";
    } else {
        QString cycles = QString::number(this->CycleCount);
        return cycles;
    }
}

QString batteryManager::get_battery_lifetime()
{
    if (this->battery.BatteryLifeTime == -1){
        return "Устройство подключено к сети";
    } else {
        int hours = this->battery.BatteryLifeTime / 3600;
        int minuts = (this->battery.BatteryLifeTime / 60) - 60 * hours;
        std::string time = std::to_string(hours) + " ч. " + std::to_string(minuts) + " м. ";
        return QString::fromStdString(time);
    }
}

QString batteryManager::get_battery_remanin_charge_time()
{
    if (this->discharging()){
        return "Устройство разряжается";
    } else if (this->charging()){
        int div = (this->get_rate() / 60);

        int timezz = (int)(this->get_max_capacity_int() - this->get_current_capacity_int());

        if (div != 0){
            timezz /= div;
        }

        int hours = timezz / 60;
        int minuts = timezz % 60;

        std::string time = std::to_string(hours) + " ч. " + std::to_string(minuts) + " м. ";

        return QString::fromStdString(time);
    } else {
        return "Не заряжается";
    }


}

QString batteryManager::get_battery_saver_status()
{
    if (this->battery.SystemStatusFlag == 0){
        return "Выключено";
    } else {
        return "Включено";
    }
}



std::string batteryManager::get_charge_speed()
{
    return std::to_string(this->information.Rate);
}

int batteryManager::get_battery_procent()
{
    int battery_life_percent = this->battery.BatteryLifePercent;
    return battery_life_percent;
}

int batteryManager::get_max_capacity_int()
{
    int capacity = this->information.MaxCapacity;
    return capacity;
}

int batteryManager::get_current_capacity_int()
{
    int capacity = this->information.RemainingCapacity;
    return capacity;
}

long batteryManager::get_rate()
{
    return this->information.Rate;
}

bool batteryManager::charging()
{
    return this->information.Charging;
}

bool batteryManager::discharging()
{
    return this->information.Discharging;
}





