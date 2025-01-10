#include "SmartHomeManager.h"

void SmartHomeManager::AddDevice(const shared_ptr<SmartDevice>& device) {
    devices.push_back(device);
}

void SmartHomeManager::ListDevices() const {
    for (const auto& device : devices) {
        device->ViewInfo();
        cout << "--------------------\n";
    }
}

void SmartHomeManager::Activate_a_Devices(int idx) {
    try {
        devices.at(idx)->Activate();            // Access element with bounds checking
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: Device index out of range: " << idx << '\n';
    }
}

void SmartHomeManager::Deactivate_a_Devices(int idx) {
    try {
        // Access element with bounds checking
        devices.at(idx)->Deactivate();
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: Device index out of range: " << idx << '\n';
    }
}

void SmartHomeManager::ActivateAllDevices() {
    for (const auto& device : devices)
        device->Activate();
}

void SmartHomeManager::DeactivateAllDevices() {
    for (const auto& device : devices)
        device->Deactivate();
}

void SmartHomeManager::InteractionEventAll() const {
    for (const auto& device : devices)
        device->InteractionEvent();
}