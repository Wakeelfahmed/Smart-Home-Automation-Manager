#include <iostream>
#include "SmartHomeManager.h"
using namespace std;
#include <windows.h>

int main() {
	SmartHomeManager manager;

	manager.AddDevice(make_shared<SecurityCamera>(1, "Front Door Camera", "CamCorp", "1080p", "Battery"));
	manager.AddDevice(make_shared<Thermostat>(2, "Living Room Thermostat", "ThermoPro"));
	manager.AddDevice(make_shared<SmartSpeaker>(3, "Kitchen Speaker", "SoundBlast", 75));
	manager.AddDevice(make_shared<SmartLight>(4, "Bedroom Light", "Lightify", 80, "RGB"));
	manager.AddDevice(make_shared<SmartDoorLock>(5, "Main Door Lock", "SecureHome", "Biometric"));
	SetConsoleOutputCP(CP_UTF8); // Set console code page to UTF-8 to display 

	std::cout << "Temperature: 25° C" << std::endl;

	int choice, choice2;
	do {
		//cout << "\nSmart Home Manager\n";
		//cout << "1. List Devices\n";
		//cout << "2. Activate a Device\n";
		//cout << "3. Deactivate a Device\n";
		//cout << "4. Activate All Devices\n";
		//cout << "5. Deactivate All Devices\n";
		//cout << "6. Interact with All Devices\n";
		//cout << "0. Exit\n";
		//cout << "Enter your choice: ";
		std::cout << "=== Smart Home Management System ===\n"
			<< "1. Add a new device\n"
			<< "2. Search for a device\n"
			<< "3. Create a room\n"
			<< "4. Add device to a room\n"
			<< "5. Remove device from a room\n"
			<< "6. List devices in a room\n"
			<< "7. Activate all devices in a room\n"
			<< "8. Deactivate all devices in a room\n"
			<< "9. Duplicate a room\n"
			<< "10. View all rooms\n"
			<< "11. Load devices and rooms from file\n"
			<< "12. Exit\n";
		cin >> choice;

		switch (choice) {
		case 1: {
			std::cout << "Enter device type (1: Light, 2: Thermostat, 3: Door Lock): ";
			int type;
			std::cin >> type;

			int id;
			std::string name, Mname;
			std::cout << "Enter device ID: ";
			std::cin >> id;
			std::cout << "Enter device name: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			std::cout << "Enter device Manufacturer: ";
			std::cin >> Mname;

			std::shared_ptr<SmartDevice> device;
			if (type == 1) {
				device = std::make_shared<SmartLight>(id, name, Mname);
			}
			else if (type == 2) {
				device = std::make_shared<Thermostat>(id, name, Mname);
			}
			else if (type == 3) {
				std::string authMethod;
				std::cout << "Enter authentication method: ";
				std::getline(std::cin, authMethod);
				device = std::make_shared<SmartDoorLock>(id, name, Mname, authMethod);
			}
			else {
				std::cout << "Invalid device type.\n";
				break;
			}

			std::string roomName;
			std::cout << "Enter room name to add the device: ";
			std::getline(std::cin, roomName);

			manager.AddDeviceToRoom(device, roomName);
			break;
		}
		case 2: {
			int id;
			std::cout << "Enter device ID to search: ";
			std::cin >> id;

			auto device = manager.SearchDevice(id);
			if (device) {
				device->ViewInfo();
				std::cout << "Select an action:\n"
					<< "1. Activate\n"
					<< "2. Deactivate\n"
					<< "3. Check connection\n"
					<< "4. Simulate interaction\n";
				int action;
				std::cin >> action;

				switch (action) {
				case 1: device->Activate(); break;
				case 2: device->Deactivate(); break;
				case 3: device->CheckConnection(); break;
				case 4: device->InteractionEvent(); break;
				default: std::cout << "Invalid action.\n"; break;
				}
			}
			else {
				std::cout << "Device not found.\n";
			}
			break;
		}
		case 3: {
			std::string roomName;
			std::cout << "Enter room name: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);

			auto room = std::make_shared<Room>(roomName);
			manager.AddDeviceToRoom(nullptr, roomName); // Create room without devices
			break;
		}
		case 4: {
			int id;
			std::string roomName;
			std::cout << "Enter device ID: ";
			std::cin >> id;
			std::cout << "Enter room name: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);

			auto device = manager.SearchDevice(id);
			if (device) {
				manager.AddDeviceToRoom(device, roomName);
			}
			else {
				std::cout << "Device not found.\n";
			}
			break;
		}
		case 5: {
			std::string roomName;
			int id;
			std::cout << "Enter room name: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);
			std::cout << "Enter device ID to remove: ";
			std::cin >> id;

			auto room = manager.SearchRoom(roomName); // Implement SearchRoom in manager
			if (room) {
				room->RemoveDevice(id);
			}
			else {
				std::cout << "Room not found.\n";
			}
			break;
		}
		case 6: {
			std::string roomName;
			std::cout << "Enter room name: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);

			shared_ptr<Room> room = manager.SearchRoom(roomName);
			if (room) {

				room->ListDevicesDetails();
			}
			else {
				std::cout << "Room not found.\n";
			}
			break;
		}
		case 7: {
			std::string roomName;
			std::cout << "Enter room name: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);

			auto room = manager.SearchRoom(roomName);
			if (room) {
				room->ActivateAllDevices();
			}
			else {
				std::cout << "Room not found.\n";
			}
			break;
		}
		case 8: {
			std::string roomName;
			std::cout << "Enter room name: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);

			auto room = manager.SearchRoom(roomName);
			if (room) {
				room->DeactivateAllDevices();
			}
			else {
				std::cout << "Room not found.\n";
			}
			break;
		}
		case 9: {
			std::string roomName;
			std::cout << "Enter room name to duplicate: ";
			std::cin.ignore();
			std::getline(std::cin, roomName);

			manager.DuplicateRoom(roomName);
			break;
		}
		case 10: {
			manager.ViewAllRooms(); // Implement ViewAllRooms in manager
			break;
		}
		case 11: {
			std::string filename;
			std::cout << "Enter filename to load from: ";
			std::cin >> filename;

			manager.LoadFromFile(filename);
			break;
		}
		case 12:
			std::cout << "Exiting system. Goodbye!\n";
			return 0;
		default:
			std::cout << "Invalid choice. Try again.\n";
		}

		/*case 1:
			manager.ListDevices();
			break;
		case 2:
			cin >> choice;
			manager.Activate_a_Devices(choice);
			break;
		case 3:
			cin >> choice;
			manager.Deactivate_a_Devices(choice);
			break;
		case 4:
			manager.ActivateAllDevices();
			break;
		case 5:
			manager.DeactivateAllDevices();
			break;
		case 6:
			manager.InteractionEventAll();
			break;
		case 0:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice, please try again.\n"; */
	} while (choice != 0);

	return 0;
}
