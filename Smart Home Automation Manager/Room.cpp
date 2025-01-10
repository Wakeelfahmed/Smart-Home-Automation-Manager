#include "Room.h"

Room::Room(const string& roomName) : name(roomName) {}

const string& Room::GetName() const { return name; }

void Room::AddDevice(shared_ptr<SmartDevice> device) {
	devices.push_back(device);
}

void Room::RemoveDevice(int id) {
	auto it = remove_if(devices.begin(), devices.end(),
		[id](const shared_ptr<SmartDevice>& device) { return device->GetID() == id; });
	if (it != devices.end()) {
		devices.erase(it, devices.end());
		cout << "Device removed successfully.\n";
	}
	else {
		cout << "Device not found in this room.\n";
	}
}

void Room::ListDevices() const {
	if (devices.empty()) {
		cout << "No devices in room " << name << ".\n";
		return;
	}
	cout << "Devices in room " << name << ":\n";
	for (const auto& device : devices) {
		cout << "- " << device->GetName() << " (ID: " << device->GetID() << ")\n";
	}
}

void Room::ListDevicesDetails() const {
	if (devices.empty()) {
		cout << "No devices in room " << name << ".\n";
		return;
	}
	cout << "Devices in room " << name << ":\n";
	for (const auto& device : devices)
		device->ViewInfo();
}

void Room::ActivateAllDevices() {
	for (auto& device : devices)
		device->Activate();
	
}

void Room::DeactivateAllDevices() {
	for (auto& device : devices) {
		device->Deactivate();
	}
}

const vector<shared_ptr<SmartDevice>>& Room::GetDevices() const {
	return devices;
}
