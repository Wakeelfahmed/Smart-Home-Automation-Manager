#include "SmartHomeManager.h"

void SmartHomeManager::AddDeviceToRoom(shared_ptr<SmartDevice> device, const string& roomName) {
	// Check if the device ID already exists in the device map
	if (deviceMap.find(device->GetID()) != deviceMap.end()) {
		cout << "Error: Device with ID " << device->GetID() << " already exists.\n";
		return;
	}

	// Add the device to the device map
	deviceMap[device->GetID()] = device;

	// Find the room with the given name in the list of rooms
	auto roomIt = find_if(rooms.begin(), rooms.end(),
		[&roomName](const unique_ptr<Room>& room) { return room->GetName() == roomName; });

	if (roomIt != rooms.end())
		(*roomIt)->AddDevice(device);	// If the room exists, add the device to it

	else {
		// If the room does not exist, create a new room
		auto newRoom = make_unique<Room>(roomName);
		newRoom->AddDevice(device);

		// Move the unique_ptr to the vector of rooms
		rooms.push_back(std::move(newRoom));
	}
}

void SmartHomeManager::AddRoom(string& roomName) {
	auto room = make_unique<Room>(roomName);	// Create a new room using a unique_ptr

	// Check if the room already exists
	auto it = find_if(rooms.begin(), rooms.end(), [&room](const unique_ptr<Room>& existingRoom) {
		return existingRoom->GetName() == room->GetName();
		});

	if (it != rooms.end())
		cout << "Room with the name " << room->GetName() << " already exists.\n";	// If the room already exists, display an error message

	else {	// If the room does not exist, add it to the list
		cout << "Room " << room->GetName() << " has been added successfully.\n";
		rooms.push_back(std::move(room));  // Move the unique_ptr into the vector
	}
}

// Searches for a device in the device map using its ID and returns a shared pointer to it.
// If the device is not found, returns nullptr.
shared_ptr<SmartDevice> SmartHomeManager::SearchDevice(int id) const {
	auto it = deviceMap.find(id);
	return (it != deviceMap.end()) ? it->second : nullptr;
}

// Searches for a room by name in the rooms vector and returns a raw pointer to the room.
// If the room is not found, returns nullptr.
Room* SmartHomeManager::SearchRoom(const string& roomName) const {
	auto roomIt = find_if(rooms.begin(), rooms.end(),
		[&roomName](const unique_ptr<Room>& room) { return room->GetName() == roomName; });

	// If the room is found, return a raw pointer to the room; otherwise, return nullptr.
	return (roomIt != rooms.end()) ? roomIt->get() : nullptr;
}

void SmartHomeManager::DuplicateRoom(const string& roomName) {
	// Find the room with the given name
	auto roomIt = find_if(rooms.begin(), rooms.end(), [&roomName](const unique_ptr<Room>& room) { return room->GetName() == roomName; });

	if (roomIt == rooms.end()) {
		cout << "Room " << roomName << " not found.\n";	    // If the room is not found, print an error message and return
		return;
	}

	auto newRoom = make_unique<Room>(roomName + "_copy");	// Create a new room with the name suffixed by "_copy"

	for (const auto& device : (*roomIt)->GetDevices()) {
		int newID = device->GetID() + 1000; // Example for unique ID generation

		// Clone the device to create a new instance (assuming Clone is implemented in SmartDevice)
		auto newDevice = device->Clone();  // Use Clone method for a deep copy

		newDevice->SetID(newID);
		newDevice->SetName(device->GetName() + "_copy");
		newRoom->AddDevice(newDevice);		// Add the new device to the duplicated room
		deviceMap[newID] = newDevice;	        // Store the new device in the device map
	}

	// Move the new room into the rooms vector to take ownership
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
	// If the device ID is not found in any room, return an error message
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
		for (auto& room : rooms)
			room->RemoveDevice(deviceToRemove->GetID());

		cout << "Device with ID " << deviceID << " has been removed successfully.\n";
		return true;
	}
	return false;
}

void SmartHomeManager::LoadFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {	// Check if the file can be opened
		cout << "Unable to open file: " + filename;
		return;
	}
	// Clear existing devices and rooms before loading new data
	deviceMap.clear();  // Clears all devices
	rooms.clear();      // Clears all rooms

	string line, roomName;
	Room* currentRoom = nullptr;	// Pointer to the current room
	string idStr, type, name, Mname, stateStr, extra;	//variables to store data
	int id;
	while (getline(file, line)) {
		// Trim whitespace
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		if (line.empty()) continue;

		if (line.rfind("Room:", 0) == 0) {
			// New room definition
			roomName = line.substr(5); // Skip "Room:"
			roomName.erase(0, roomName.find_first_not_of(" \t"));
			roomName.erase(roomName.find_last_not_of(" \t") + 1);

			//rooms.emplace_back(Room(roomName));
			rooms.emplace_back(make_unique<Room>(roomName));
			currentRoom = rooms.back().get(); // Get raw pointer from shared_ptr
		}
		else {
			if (!currentRoom)
				throw runtime_error("Device entry found before any room declaration.");

			istringstream iss(line);

			if (!getline(iss, idStr, ',') || !getline(iss, type, ',') || !getline(iss, name, ',') || !getline(iss, Mname, ',') || !getline(iss, stateStr, ','))
				throw runtime_error("Malformed device entry: " + line);

			id = stoi(idStr);

			if (type == "SmartLight") {
				if (!getline(iss, extra, ','))	//Read  color
					throw runtime_error("Missing color for SmartLight: " + line);
				AddDeviceToRoom(make_shared<SmartLight>(id, name, Mname, stoi(stateStr)/*Bightness*/, extra /*color*/), roomName);
			}
			else if (type == "Thermostat")
				AddDeviceToRoom(make_shared<Thermostat>(id, name, Mname, float(stod(stateStr))), roomName);
			else if (type == "SmartDoorLock")
				AddDeviceToRoom(make_shared<SmartDoorLock>(id, name, Mname, stateStr), roomName);
			else if (type == "WashingMachine") {
				if (!getline(iss, extra, ','))	//Read time duration
					throw runtime_error("Missing duration for WashingMachine: " + line);
				string dur = extra;
				if (!getline(iss, extra, ','))	//Read load capacity
					throw runtime_error("Missing load Capacity: " + line);
				AddDeviceToRoom(make_shared<SmartWashingMachine>(id, name, Mname, stateStr, stoi(dur), stoi(extra)), roomName);
			}
			else if (type == "IrrigationSystem") {
				if (!getline(iss, extra, ','))	//Read water schedule 
					throw runtime_error("Missing water schedule for IrrigationSystem: " + line);
				string Sche = extra;
				if (!getline(iss, extra, ',')) // Read water usage
					throw runtime_error("Missing water usage for IrrigationSystem: " + line);
				AddDeviceToRoom(make_shared<IrrigationSystem>(id, name, Mname, stoi(stateStr) /*dur*/, Sche /*Sche*/, stoi(extra)/*usage*/), roomName);
			}
			else if (type == "SecurityCamera") {
				if (!getline(iss, extra, ','))	//Read power source 
					throw runtime_error("Missing Power Source for SecurityCamera: " + line);
				AddDeviceToRoom(make_shared<SecurityCamera>(id, name, Mname, stateStr, extra), roomName);
			}
			else if (type == "SmartSpeaker")
				AddDeviceToRoom(make_shared<SmartSpeaker>(id, name, Mname, stoi(stateStr)), roomName);
			else
				throw runtime_error("Unknown device type: " + type);
		}
	}
	file.close();	// Close the file after reading
}