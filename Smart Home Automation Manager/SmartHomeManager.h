#ifndef SMARTHOMEMANAGER_H
#define SMARTHOMEMANAGER_H

#include <vector>
#include "SmartDevice.h"
#include "SecurityCamera.h"
#include "Thermostat.h"
#include "SmartSpeaker.h"
#include "SmartLight.h"
#include "SmartDoorLock.h"
#include "SmartWashingMachine.h"
#include "IrrigationSystem.h"
#include "Room.h"

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>

class SmartHomeManager {
	unordered_map<int, shared_ptr<SmartDevice>> deviceMap;
	vector<unique_ptr<Room>> rooms;

public:
	void AddDeviceToRoom(shared_ptr<SmartDevice> device, const string& roomName);
	void AddRoom(string& room);
	shared_ptr<SmartDevice> SearchDevice(int id) const;
	Room* SearchRoom(const string& roomName) const;
	void DuplicateRoom(const string& roomName);
	void ViewAllRooms() const;
	string GetRoomNameByDeviceID(int deviceID) const;
	bool RemoveDeviceByID(int deviceID);
	void LoadFromFile(const string& filename);
};

#endif 
