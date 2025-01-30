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
	// Stores all smart devices, mapped by their unique ID
	unordered_map<int, shared_ptr<SmartDevice>> deviceMap;

	// Stores a collection of rooms in the smart home
	vector<unique_ptr<Room>> rooms;

public:
	// Adds a smart device to a specified room
	void AddDeviceToRoom(shared_ptr<SmartDevice> device, const string& roomName);

	// Creates a new room and adds it to the smart home
	void AddRoom(string& room);

	// Searches for a device by its ID and returns a shared pointer to it
	shared_ptr<SmartDevice> SearchDevice(int id) const;

	// Searches for a room by its name and returns a pointer to it (no ownership transfer)
	Room* SearchRoom(const string& roomName) const;

	// Creates a duplicate of an existing room with the same devices
	void DuplicateRoom(const string& roomName);

	// Displays all rooms in the smart home
	void ViewAllRooms() const;

	// Retrieves the name of the room containing a device with the given ID
	string GetRoomNameByDeviceID(int deviceID) const;

	// Removes a device by its ID from both the room and the device map
	bool RemoveDeviceByID(int deviceID);

	// Loads smart home configuration from a file
	void LoadFromFile(const string& filename);
};

#endif 


//#ifndef SMARTHOMEMANAGER_H
//#define SMARTHOMEMANAGER_H
//
//#include <vector>
//#include "SmartDevice.h"
//#include "SecurityCamera.h"
//#include "Thermostat.h"
//#include "SmartSpeaker.h"
//#include "SmartLight.h"
//#include "SmartDoorLock.h"
//#include "SmartWashingMachine.h"
//#include "IrrigationSystem.h"
//#include "Room.h"
//
//#include <unordered_map>
//#include <fstream>
//#include <sstream>
//#include <stdexcept>
//
//class SmartHomeManager {
//	unordered_map<int, shared_ptr<SmartDevice>> deviceMap;
//	vector<unique_ptr<Room>> rooms;
//
//public:
//	void AddDeviceToRoom(shared_ptr<SmartDevice> device, const string& roomName);
//	void AddRoom(string& room);
//	shared_ptr<SmartDevice> SearchDevice(int id) const;
//	Room* SearchRoom(const string& roomName) const;		// Return a pointer to the room rather ownwership transfer
//	void DuplicateRoom(const string& roomName);
//	void ViewAllRooms() const;
//	string GetRoomNameByDeviceID(int deviceID) const;
//	bool RemoveDeviceByID(int deviceID);
//	void LoadFromFile(const string& filename);
//};
//
//#endif 
