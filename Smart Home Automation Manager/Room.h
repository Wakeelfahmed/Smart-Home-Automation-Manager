#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>
#include <iostream>
#include "SmartDevice.h"

class Room {
	string name;
	vector<shared_ptr<SmartDevice>> devices;

public:
	Room(const string& roomName);
	const string& GetName() const;
	void AddDevice(shared_ptr<SmartDevice> device);
	bool RemoveDevice(int id);
	void ListDevices() const;
	void ListDevicesDetails() const;
	void ActivateAllDevices();
	void DeactivateAllDevices();
	const vector<shared_ptr<SmartDevice>>& GetDevices() const;
};

#endif // ROOM_H
