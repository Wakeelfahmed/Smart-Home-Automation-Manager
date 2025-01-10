#include "SmartDevice.h"

SmartDevice::SmartDevice(int id, const string& name, const string& manufacturer) : id(id), name(name), manufacturer(manufacturer), status(false) {}

SmartDevice::~SmartDevice() {}

void SmartDevice::Activate() {
	status = true;
	cout << name << " activated.\n";
}

void SmartDevice::Deactivate() {
	status = false;
	cout << name << " deactivated.\n";
}

bool SmartDevice::GetStatus() const { return status; }

void SmartDevice::ViewInfo() const {
	cout << "ID: " << id << "\tName: " << name << "\tManufacturer: " << manufacturer << "\t\tStatus: " << (status ? "Active" : "Inactive") << '\n';
}

bool SmartDevice::CheckConnection() const { return status; }

int SmartDevice::GetID() const { return id; }

void SmartDevice::SetID(int id) { this->id = id; }

void SmartDevice::SetName(const string& name) { this->name = name; }

const string& SmartDevice::GetName() const { return name; }