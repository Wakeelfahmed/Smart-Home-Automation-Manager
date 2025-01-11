#include "SmartHomeManager.h"

void SmartHomeManager::AddDeviceToRoom(shared_ptr<SmartDevice> device, const string& roomName) {
	if (deviceMap.find(device->GetID()) != deviceMap.end()) {
		cout << "Error: Device with ID " << device->GetID() << " already exists.\n";
		return;
	}
	deviceMap[device->GetID()] = device;

	auto roomIt = find_if(rooms.begin(), rooms.end(),
		[&roomName](const unique_ptr<Room>& room) { return room->GetName() == roomName; });

	if (roomIt != rooms.end()) {
		(*roomIt)->AddDevice(device);
	}
	else {
		auto newRoom = make_unique<Room>(roomName);
		newRoom->AddDevice(device);
		rooms.push_back(std::move(newRoom));  // Move the unique_ptr into the vector
	}
}

void SmartHomeManager::AddRoom(string& roomName) {
	auto room = make_unique<Room>(roomName);

	// Check if the room already exists
	auto it = find_if(rooms.begin(), rooms.end(), [&room](const unique_ptr<Room>& existingRoom) {
		return existingRoom->GetName() == room->GetName();
		});

	if (it != rooms.end()) {
		cout << "Room with the name " << room->GetName() << " already exists.\n";
	}
	else {
		rooms.push_back(std::move(room));  // Move the unique_ptr into the vector
		cout << "Room " << room->GetName() << " has been added successfully.\n";
	}
}

shared_ptr<SmartDevice> SmartHomeManager::SearchDevice(int id) const {
	auto it = deviceMap.find(id);
	return (it != deviceMap.end()) ? it->second : nullptr;
}

Room* SmartHomeManager::SearchRoom(const string& roomName) const {
	auto roomIt = find_if(rooms.begin(), rooms.end(),
		[&roomName](const unique_ptr<Room>& room) { return room->GetName() == roomName; });

	//return (roomIt != rooms.end()) ? *roomIt : nullptr;
	return (roomIt != rooms.end()) ? roomIt->get() : nullptr;
}

void SmartHomeManager::DuplicateRoom(const string& roomName) {
	auto roomIt = find_if(rooms.begin(), rooms.end(), [&roomName](const unique_ptr<Room>& room) { return room->GetName() == roomName; });

	if (roomIt == rooms.end()) {
		cout << "Room " << roomName << " not found.\n";
		return;
	}

	auto newRoom = make_unique<Room>(roomName + "_copy");
	for (const auto& device : (*roomIt)->GetDevices()) {
		int newID = device->GetID() + 1000; // Example for unique ID generation
		//auto newDevice = device;   // Ensure a Clone method is implemented in SmartDevice
		// Use the copy constructor to create a new device
		auto newDevice = device->Clone();  // Use Clone method for a deep copy

		newDevice->SetID(newID);
		newDevice->SetName(device->GetName() + "_copy");
		newRoom->AddDevice(newDevice);
		deviceMap[newID] = newDevice;
	}
	rooms.push_back(std::move(newRoom));  // Use std::move to transfer ownership

	cout << "Room duplicated successfully.\n";
}

void SmartHomeManager::ViewAllRooms() const {
	for (const auto& room : rooms) {
		room->ListDevices();
		cout << "--------------------\n";
	}
}

string SmartHomeManager::GetRoomNameByDeviceID(int deviceID) const {
	// Search for the device in the deviceMap using the device ID
	auto deviceIt = deviceMap.find(deviceID);
	if (deviceIt != deviceMap.end()) {
		// If the device is found, search through all rooms to find which room contains the device
		for (const auto& room : rooms) {
			for (const auto& device : room->GetDevices()) {
				if (device->GetID() == deviceID) {
					// Return the room name if the device is found
					return room->GetName();
				}
			}
		}
	}
	// If device ID is not found, return an error message
	return "Device not found in any room";
}

bool SmartHomeManager::RemoveDeviceByID(int deviceID) {
	// Search for the device in the deviceMap using the device ID
	auto deviceIt = deviceMap.find(deviceID);
	if (deviceIt != deviceMap.end()) {
		// Get the device to be removed
		shared_ptr<SmartDevice> deviceToRemove = deviceIt->second;

		// Remove the device from the deviceMap
		deviceMap.erase(deviceIt);

		// Find the room that contains the device and remove it from the room
		for (auto& room : rooms) {
			room->RemoveDevice(deviceToRemove->GetID());
		}

		cout << "Device with ID " << deviceID << " has been removed successfully.\n";
		return true;
	}
	return false;
}

void SmartHomeManager::LoadFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Unable to open file: " + filename;
		return;
	}
	deviceMap.clear();  // Clears all devices
	rooms.clear();      // Clears all rooms

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
			rooms.emplace_back(make_unique<Room>(roomName));
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

			else if (type == "Thermostat") {
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
			else if (type == "WashingMachine") {
				if (!getline(iss, extra, ',')) {
					throw runtime_error("Missing power t: " + line);
				}
				currentRoom->AddDevice(make_shared<SmartWashingMachine>(id, name, Mname, stateStr, stoi(extra)));
			}
			else if (type == "IrrigationSystem") {
				if (!getline(iss, extra, ',')) {
					throw runtime_error("Missing water flow rate for IrrigationSystem: " + line);
				}
				double flowRate = stod(extra);
				currentRoom->AddDevice(make_shared<IrrigationSystem>(id, name, Mname, float(flowRate)));
			}
			else if (type == "SecurityCamera") {
				if (!getline(iss, extra, ',')) {
					throw runtime_error("Missing resolution for SecurityCamera: " + line);
				}
				string resolution = extra;
				if (!getline(iss, extra, ',')) {
					throw runtime_error("Missing power source for SecurityCamera: " + line);
				}
				string powerSource = extra;
				currentRoom->AddDevice(make_shared<SecurityCamera>(id, name, Mname, resolution, powerSource));
			}
			else if (type == "SmartSpeaker") {
				if (!getline(iss, extra, ',')) {
					throw runtime_error("Missing volume for SmartSpeaker: " + line);
				}
				int volume = stoi(extra);
				currentRoom->AddDevice(make_shared<SmartSpeaker>(id, name, Mname, volume));
			}

			else {
				throw runtime_error("Unknown device type: " + type);
			}
		}
	}

	file.close();
}