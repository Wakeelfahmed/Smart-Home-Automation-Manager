#include "SmartDevice.h"

// Constructor to initialize a SmartDevice with the provided id, name, and manufacturer
SmartDevice::SmartDevice(int id, const string& name, const string& manufacturer) : id(id), name(name), manufacturer(manufacturer), status(false) {}

// Destructor for SmartDevice (empty because no resources need to be freed)
SmartDevice::~SmartDevice() {}

// Activates the device and sets its status to true (active)
void SmartDevice::Activate() {
	status = true;
	cout << name << " activated.\n";
}

// Deactivates the device and sets its status to false (inactive)
void SmartDevice::Deactivate() {
	status = false;
	cout << name << " deactivated.\n";
}

// Returns the current status of the device (true if active, false if inactive)
bool SmartDevice::GetStatus() const { return status; }

// Displays the basic information of the device, including its id, name, manufacturer, and status
void SmartDevice::ViewInfo() const {
	cout << "ID: " << id << "\tName: " << name << "\tManufacturer: " << manufacturer << "\tStatus: " << (status ? "Active" : "Inactive") << '\t';
}

// Checks if the device is connected (based on its status)
bool SmartDevice::CheckConnection() const { return status; }

// Getter for the device id
int SmartDevice::GetID() const { return id; }

// Setter for the device id
void SmartDevice::SetID(int id) { this->id = id; }

// Setter for the device name
void SmartDevice::SetName(const string& name) { this->name = name; }

// Getter for the device name
const string& SmartDevice::GetName() const { return name; }