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
	vector<shared_ptr<Room>> rooms;

public:
	void AddDeviceToRoom(shared_ptr<SmartDevice> device, const string& roomName) {
		if (deviceMap.find(device->GetID()) != deviceMap.end()) {
			cout << "Error: Device with ID " << device->GetID() << " already exists.\n";
			return;
		}
		deviceMap[device->GetID()] = device;

		auto roomIt = find_if(rooms.begin(), rooms.end(),
			[&roomName](const shared_ptr<Room>& room) { return room->GetName() == roomName; });

		if (roomIt != rooms.end()) {
			(*roomIt)->AddDevice(device);
		}
		else {
			auto newRoom = make_shared<Room>(roomName);
			newRoom->AddDevice(device);
			rooms.push_back(newRoom);
		}
	}
	shared_ptr<SmartDevice> SearchDevice(int id) const {
		auto it = deviceMap.find(id);
		return (it != deviceMap.end()) ? it->second : nullptr;
	}

	shared_ptr<Room> SearchRoom(const string& roomName) const {
		auto roomIt = find_if(rooms.begin(), rooms.end(),
			[&roomName](const shared_ptr<Room>& room) { return room->GetName() == roomName; });

		return (roomIt != rooms.end()) ? *roomIt : nullptr;
	}

	void DuplicateRoom(const string& roomName) {
		auto roomIt = find_if(rooms.begin(), rooms.end(), [&roomName](const shared_ptr<Room>& room) { return room->GetName() == roomName; });

		if (roomIt == rooms.end()) {
			cout << "Room " << roomName << " not found.\n";
			return;
		}

		auto newRoom = make_shared<Room>(roomName + "_copy");
		for (const auto& device : (*roomIt)->GetDevices()) {
			int newID = device->GetID() + 1000; // Example for unique ID generation
			//auto newDevice = device;   // Ensure a Clone method is implemented in SmartDevice
			// Use the copy constructor to create a new device
			auto newDevice = device->Clone();  // Use Clone method for a deep copy

			//auto newDevice = make_shared<SmartDevice>(*device);
			newDevice->SetID(newID);
			newDevice->SetName(device->GetName() + "_copy");
			newRoom->AddDevice(newDevice);
			deviceMap[newID] = newDevice;
		}
		rooms.push_back(newRoom);
		cout << "Room duplicated successfully.\n";
	}
	void ViewAllRooms() const {
		for (const auto& room : rooms) {
			room->ListDevices();
			cout << "--------------------\n";
		}
	}
	void LoadFromFile(const string& filename) {
		ifstream file(filename);
		if (!file.is_open())
			throw runtime_error("Unable to open file: " + filename);

		string line;
		Room* currentRoom = nullptr;

		while (getline(file, line)) {
			// Trim whitespace
			line.erase(0, line.find_first_not_of(" \t"));
			line.erase(line.find_last_not_of(" \t") + 1);

			if (line.empty()) continue;

			if (line.rfind("Room:", 0) == 0) {
				// New room definition
				string roomName = line.substr(5); // Skip "Room:"
				roomName.erase(0, roomName.find_first_not_of(" \t"));
				roomName.erase(roomName.find_last_not_of(" \t") + 1);

				//rooms.emplace_back(Room(roomName));
				rooms.emplace_back(make_shared<Room>(roomName));
				currentRoom = rooms.back().get(); // Get raw pointer from shared_ptr
			}
			else {
				if (!currentRoom) {
					throw runtime_error("Device entry found before any room declaration.");
				}

				istringstream iss(line);
				string idStr, type, name, stateStr, Mname, extra;

				if (!getline(iss, idStr, ',') ||
					!getline(iss, type, ',') ||
					!getline(iss, name, ',') ||
					!getline(iss, Mname, ',') ||
					!getline(iss, stateStr, ',')) {
					throw runtime_error("Malformed device entry: " + line);
				}

				int id = stoi(idStr);
				bool state = (stateStr == "true");

				if (type == "SmartLight")
					currentRoom->AddDevice(make_shared<SmartLight>(id, name, Mname, state));

				else if (type == "SmartThermostat") {
					if (!getline(iss, extra, ',')) {
						throw runtime_error("Missing temperature for SmartThermostat: " + line);
					}
					double temperature = stod(extra);
					currentRoom->AddDevice(make_shared<Thermostat>(id, name, Mname, float(temperature)));
				}
				else if (type == "SmartDoorLock") {
					if (!getline(iss, extra, ',')) {
						throw runtime_error("Missing authMethod for SmartDoorLock: " + line);
					}
					currentRoom->AddDevice(make_shared<SmartDoorLock>(id, name, Mname, extra));
				}
				else {
					throw runtime_error("Unknown device type: " + type);
				}
			}
		}

		file.close();
	}
};

#endif 
