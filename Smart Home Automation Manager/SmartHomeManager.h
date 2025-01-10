#ifndef SMARTHOMEMANAGER_H
#define SMARTHOMEMANAGER_H

#include <vector>
#include "SmartDevice.h"
#include "SecurityCamera.h"
#include "Thermostat.h"
#include "SmartSpeaker.h"
#include "SmartLight.h"
#include "SmartDoorLock.h"
#include "Room.h"

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>

class SmartHomeManager {
private:
	int IDCounter = 0;
	vector<shared_ptr<SmartDevice>> devices;
	std::unordered_map<int, std::shared_ptr<SmartDevice>> deviceMap;
	std::vector<std::shared_ptr<Room>> rooms;


public:
	void AddDevice(const shared_ptr<SmartDevice>& device);
	void AddDeviceToRoom(std::shared_ptr<SmartDevice> device, const std::string& roomName) {
		if (deviceMap.find(device->GetID()) != deviceMap.end()) {
			std::cout << "Error: Device with ID " << device->GetID() << " already exists.\n";
			return;
		}
		deviceMap[device->GetID()] = device;

		auto roomIt = std::find_if(rooms.begin(), rooms.end(),
			[&roomName](const std::shared_ptr<Room>& room) { return room->GetName() == roomName; });

		if (roomIt != rooms.end()) {
			(*roomIt)->AddDevice(device);
		}
		else {
			auto newRoom = std::make_shared<Room>(roomName);
			newRoom->AddDevice(device);
			rooms.push_back(newRoom);
		}
		IDCounter++;
	}
	std::shared_ptr<SmartDevice> SearchDevice(int id) const {
		auto it = deviceMap.find(id);
		return (it != deviceMap.end()) ? it->second : nullptr;
	}
	std::shared_ptr<Room> SearchRoom(const std::string& roomName) const {
		auto roomIt = std::find_if(rooms.begin(), rooms.end(),
			[&roomName](const std::shared_ptr<Room>& room) { return room->GetName() == roomName; });

		return (roomIt != rooms.end()) ? *roomIt : nullptr;
	}
	void DuplicateRoom(const std::string& roomName) {
		auto roomIt = std::find_if(rooms.begin(), rooms.end(),
			[&roomName](const std::shared_ptr<Room>& room) { return room->GetName() == roomName; });

		if (roomIt == rooms.end()) {
			std::cout << "Room " << roomName << " not found.\n";
			return;
		}

		auto newRoom = std::make_shared<Room>(roomName + "_copy");
		for (const auto& device : (*roomIt)->GetDevices()) {
			int newID = device->GetID() + 1000; // Example for unique ID generation
			auto newDevice = device;   // Ensure a Clone method is implemented in SmartDevice
			newDevice->SetID(newID);
			newDevice->SetName(device->GetName() + "_copy");
			newRoom->AddDevice(newDevice);
			deviceMap[newID] = newDevice;
		}
		rooms.push_back(newRoom);
		std::cout << "Room duplicated successfully.\n";
	}
	void ViewAllRooms() const {
		for (const auto& room : rooms) {
			room->ListDevices();
			std::cout << "--------------------\n";
		}
	}
	void ListDevices() const;
	void ActivateAllDevices();
	void DeactivateAllDevices();
	void InteractionEventAll() const;
	void Activate_a_Devices(int idx);
	void Deactivate_a_Devices(int idx);

	//void LoadFromFile(const std::string& filename) {
	//	std::ifstream file(filename);
	//	if (!file.is_open()) {
	//		throw std::runtime_error("Unable to open file: " + filename);
	//	}

	//	std::string line;
	//	Room* currentRoom = nullptr;

	//	while (std::getline(file, line)) {
	//		// Trim whitespace
	//		line.erase(0, line.find_first_not_of(" \t"));
	//		line.erase(line.find_last_not_of(" \t") + 1);

	//		if (line.empty()) continue;

	//		if (line.rfind("Room:", 0) == 0) {
	//			// New room definition
	//			std::string roomName = line.substr(5); // Skip "Room:"
	//			roomName.erase(0, roomName.find_first_not_of(" \t"));
	//			roomName.erase(roomName.find_last_not_of(" \t") + 1);

	//			rooms.emplace_back(Room(roomName));
	//			currentRoom = &rooms.back();
	//		}
	//		else {
	//			if (!currentRoom) {
	//				throw std::runtime_error("Device entry found before any room declaration.");
	//			}

	//			std::istringstream iss(line);
	//			std::string idStr, type, name, stateStr, extra;

	//			if (!std::getline(iss, idStr, ',') ||
	//				!std::getline(iss, type, ',') ||
	//				!std::getline(iss, name, ',') ||
	//				!std::getline(iss, stateStr, ',')) {
	//				throw std::runtime_error("Malformed device entry: " + line);
	//			}

	//			int id = std::stoi(idStr);
	//			bool state = (stateStr == "true");

	//			if (type == "SmartLight") {
	//				currentRoom->AddDevice(std::make_shared<SmartLight>(id, name, state));
	//			}
	//			else if (type == "SmartThermostat") {
	//				if (!std::getline(iss, extra, ',')) {
	//					throw std::runtime_error("Missing temperature for SmartThermostat: " + line);
	//				}
	//				double temperature = std::stod(extra);
	//				currentRoom->AddDevice(std::make_shared<Thermostat>(id, name, state, temperature));
	//			}
	//			else if (type == "SmartDoorLock") {
	//				if (!std::getline(iss, extra, ',')) {
	//					throw std::runtime_error("Missing authMethod for SmartDoorLock: " + line);
	//				}
	//				currentRoom->AddDevice(std::make_shared<SmartDoorLock>(id, name, state, extra));
	//			}
	//			else {
	//				throw std::runtime_error("Unknown device type: " + type);
	//			}
	//		}
	//	}

	//	file.close();
	//}

	void LoadFromFile(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file: " + filename);
		}

		std::string line;
		Room* currentRoom = nullptr;

		while (std::getline(file, line)) {
			// Trim whitespace
			line.erase(0, line.find_first_not_of(" \t"));
			line.erase(line.find_last_not_of(" \t") + 1);

			if (line.empty()) continue;

			if (line.rfind("Room:", 0) == 0) {
				// New room definition
				std::string roomName = line.substr(5); // Skip "Room:"
				roomName.erase(0, roomName.find_first_not_of(" \t"));
				roomName.erase(roomName.find_last_not_of(" \t") + 1);

				//rooms.emplace_back(Room(roomName));
				rooms.emplace_back(std::make_shared<Room>(roomName));
				currentRoom = rooms.back().get(); // Get raw pointer from shared_ptr
			}
			else {
				if (!currentRoom) {
					throw std::runtime_error("Device entry found before any room declaration.");
				}

				std::istringstream iss(line);
				std::string idStr, type, name, stateStr, Mname, extra;

				if (!std::getline(iss, idStr, ',') ||
					!std::getline(iss, type, ',') ||
					!std::getline(iss, name, ',') ||
					!std::getline(iss, Mname, ',') ||
					!std::getline(iss, stateStr, ',')) {
					throw std::runtime_error("Malformed device entry: " + line);
				}

				int id = std::stoi(idStr);
				bool state = (stateStr == "true");

				if (type == "SmartLight") {
					currentRoom->AddDevice(std::make_shared<SmartLight>(id, name, Mname, state));
				}
				else if (type == "SmartThermostat") {
					if (!std::getline(iss, extra, ',')) {
						throw std::runtime_error("Missing temperature for SmartThermostat: " + line);
					}
					double temperature = std::stod(extra);
					currentRoom->AddDevice(std::make_shared<Thermostat>(id, name, Mname, temperature));
				}
				else if (type == "SmartDoorLock") {
					if (!std::getline(iss, extra, ',')) {
						throw std::runtime_error("Missing authMethod for SmartDoorLock: " + line);
					}
					std::shared_ptr<SmartDevice> device;
					//device = std::make_shared<SmartDoorLock>(id, name, Mname, extra);

					currentRoom->AddDevice(std::make_shared<SmartDoorLock>(id, name, Mname, extra));
				}
				else {
					throw std::runtime_error("Unknown device type: " + type);
				}
			}
		}

		file.close();
	}

	//const std::vector<Room>& GetRooms() const { return rooms; }

};

#endif 
