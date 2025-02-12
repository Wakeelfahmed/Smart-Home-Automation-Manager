#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>
#include <iostream>
#include "SmartDevice.h"

// Represents a room that contains multiple smart devices
class Room {
	string name;	// Name of the room
	vector<shared_ptr<SmartDevice>> devices;	// List of smart devices in the room

public:
	// Constructor to initialize the room with a given name
	Room(const string& roomName);

	// Returns the name of the room
	const string& GetName() const;

	// Adds a smart device to the room
	void AddDevice(shared_ptr<SmartDevice> device);

	// Removes a smart device by its ID, returns true if successful
	bool RemoveDevice(int id);

	// Lists the names of all devices in the room
	void ListDevices() const;

	// Displays detailed information about all devices in the room
	void ListDevicesDetails() const;

	// Activates all devices in the room
	void ActivateAllDevices();

	// Deactivates all devices in the room
	void DeactivateAllDevices();

	// Returns a reference to the vector of smart devices
	const vector<shared_ptr<SmartDevice>>& GetDevices() const;
};

#endif // ROOM_H
