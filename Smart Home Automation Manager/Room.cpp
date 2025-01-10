#include "Room.h"

Room::Room(const std::string& roomName) : name(roomName) {}

const std::string& Room::GetName() const { return name; }

void Room::AddDevice(std::shared_ptr<SmartDevice> device) {
	devices.push_back(device);
}

void Room::RemoveDevice(int id) {
	auto it = std::remove_if(devices.begin(), devices.end(),
		[id](const std::shared_ptr<SmartDevice>& device) { return device->GetID() == id; });
	if (it != devices.end()) {
		devices.erase(it, devices.end());
		std::cout << "Device removed successfully.\n";
	}
	else {
		std::cout << "Device not found in this room.\n";
	}
}

void Room::ListDevices() const {
	if (devices.empty()) {
		std::cout << "No devices in room " << name << ".\n";
		return;
	}
	std::cout << "Devices in room " << name << ":\n";
	for (const auto& device : devices) {
		std::cout << "- " << device->GetName() << " (ID: " << device->GetID() << ")\n";
	}
}

void Room::ListDevicesDetails() const {
	if (devices.empty()) {
		std::cout << "No devices in room " << name << ".\n";
		return;
	}
	std::cout << "Devices in room " << name << ":\n";
	for (const auto& device : devices)
		device->ViewInfo();
}

void Room::ActivateAllDevices() {
	for (auto& device : devices) {
		device->Activate();
	}
}

void Room::DeactivateAllDevices() {
	for (auto& device : devices) {
		device->Deactivate();
	}
}

const std::vector<std::shared_ptr<SmartDevice>>& Room::GetDevices() const {
	return devices;
}
