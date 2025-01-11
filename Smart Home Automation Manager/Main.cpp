#include <iostream>
#include <windows.h>	// For UTF-8 support & the file be saved as UTF-8 format

#include "SmartHomeManager.h"
using namespace std;

int main() {
	SmartHomeManager manager;

	// Porch
	manager.AddDeviceToRoom(make_shared<SecurityCamera>(1, "FrontDoor_Camera", "CamCorp", "1080p", "Battery"), "Porch");
	manager.AddDeviceToRoom(make_shared<SmartLight>(2, "Light", "Philips", 100, "Warm"), "Porch");
	manager.AddDeviceToRoom(make_shared<SmartDoorLock>(3, "Main_Lock", "SecureHome", "Biometric"), "Porch");

	// Living Room
	manager.AddDeviceToRoom(make_shared<Thermostat>(4, "Thermostat", "ThermoPro"), "Living");
	manager.AddDeviceToRoom(make_shared<SmartSpeaker>(5, "Speaker", "Audionic", 80), "Living");
	manager.AddDeviceToRoom(make_shared<SmartLight>(6, "Light", "Philips", 75, "White"), "Living");

	// Kitchen
	manager.AddDeviceToRoom(make_shared<SmartSpeaker>(7, "Speaker", "Audionic", 70), "Kitchen");
	manager.AddDeviceToRoom(make_shared<SmartLight>(8, "Light", "Philips", 85, "White"), "Kitchen");

	// Bedroom
	manager.AddDeviceToRoom(make_shared<SmartLight>(9, "Light", "Philips", 70, "Warm"), "Bedroom");
	manager.AddDeviceToRoom(make_shared<Thermostat>(10, "Thermostat", "ThermoPro"), "Bedroom");
	manager.AddDeviceToRoom(make_shared<SmartSpeaker>(11, "Speaker", "Audionic", 60), "Bedroom");

	// Garden
	manager.AddDeviceToRoom(make_shared<IrrigationSystem>(12, "Irrigation System", "GreenTech"), "Garden");
	manager.AddDeviceToRoom(make_shared<SmartLight>(13, "Light", "Philips", 50, "Cool"), "Garden");

	// Laundry Room
	manager.AddDeviceToRoom(make_shared<SmartWashingMachine>(14, "Washer", "Samsung", "Quick Wash", 45, 8), "Laundry");
	manager.AddDeviceToRoom(make_shared<SmartLight>(15, "Light", "Philips", 60, "White"), "Laundry");

	// Garage
	manager.AddDeviceToRoom(make_shared<SecurityCamera>(16, "Camera", "CamCorp", "720p", "Wired"), "Garage");
	manager.AddDeviceToRoom(make_shared<SmartDoorLock>(17, "Door Lock", "SecureHome", "Keypad"), "Garage");
	manager.AddDeviceToRoom(make_shared<SmartLight>(18, "Light", "Lightify", 90, "White"), "Garage");

	// Bathroom
	manager.AddDeviceToRoom(make_shared<Thermostat>(19, "Thermostat", "ThermoPro"), "Bathroom");
	manager.AddDeviceToRoom(make_shared<SmartLight>(20, "Light", "Lightify", 75, "White"), "Bathroom");

	SetConsoleOutputCP(CP_UTF8); // Set console code page to UTF-8 to display 

	short choice;
	do {
		cout << "=== Smart Home Management System ===\n"
			<< "1. Add a new device\t"
			<< "2. Search for a device\t\t"
			<< "3. Activate all devices of room\t"
			<< "4. Deactivate all devices of room\n"
			<< "5. Create a room\t"
			<< "6. Move a device across room\t"
			<< "7. Remove device from room\t"
			<< "8. List devices in a room\n"
			<< "9. Duplicate room\t"
			<< "10. View all rooms\t\t"
			<< "11. Load devices & rooms from file\n"
			<< "12. Exit\n";
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Enter device type (1: Light, 2: Thermostat, 3: Door Lock, 4: Camera, 5: Speaker): ";
			short type;
			cin >> type;

			int id;		string name, Mname;
			cout << "Enter device ID: ";				cin >> id;
			cout << "Enter device name: ";				cin >> name;
			cout << "Enter device Manufacturer: ";		cin >> Mname;

			shared_ptr<SmartDevice> device;
			if (type == 1)
				device = make_shared<SmartLight>(id, name, Mname);
			else if (type == 2)
				device = make_shared<Thermostat>(id, name, Mname);
			else if (type == 3) {
				string authMethod;
				cout << "Enter authentication method: "; cin >> authMethod;
				device = make_shared<SmartDoorLock>(id, name, Mname, authMethod);
			}
			else if (type == 4) {
				string res, power;
				cout << "Enter camera resolution: ";	cin >> res;
				cout << "Enter power source: ";			cin >> power;
				device = make_shared<SecurityCamera>(id, name, Mname, res, power);
			}
			else if (type == 5) {
				int volume;
				cout << "Enter volume level: ";			cin >> volume;
				device = make_shared<SmartSpeaker>(id, name, Mname, volume);
			}
			else {
				cout << "Invalid device type.\n";
				break;
			}

			string roomName;
			cout << "Enter room name to add the device: ";	cin >> roomName;

			manager.AddDeviceToRoom(device, roomName);
			break;
		}
		case 2: {
			int id;
			cout << "Enter device ID to search: ";			cin >> id;

			auto device = manager.SearchDevice(id);
			if (device) {
				device->ViewInfo();
				cout << "Select an action:\n"
					<< "1. Activate\t"
					<< "2. Deactivate\n"
					<< "3. Check connection\t"
					<< "4. Simulate interaction\n";
				short action;		cin >> action;

				switch (action) {
				case 1: device->Activate(); break;
				case 2: device->Deactivate(); break;
				case 3:
					if (device->CheckConnection())
						cout << "Up & Running";
					else
						cout << "Inactive or Malfunctioning";
					break;
				case 4: device->InteractionEvent(); break;
				default: cout << "Invalid action.\n"; break;
				}
			}
			else
				cout << "Device not found.\n";
			break;
		}
		case 3: {
			string roomName;
			cout << "Enter room name: ";		cin >> roomName;

			auto room = manager.SearchRoom(roomName);
			if (room)
				room->ActivateAllDevices();
			else
				cout << "Room not found.\n";

			break;
		}
		case 4: {
			string roomName;
			cout << "Enter room name: ";		cin >> roomName;

			auto room = manager.SearchRoom(roomName);
			if (room)
				room->DeactivateAllDevices();
			else
				cout << "Room not found.\n";

			break;
		}
		case 5: {
			string roomName;
			cout << "Enter room name: ";		cin >> roomName;
			manager.AddRoom(roomName);
			break;
		}
		case 6: {
			int id;
			string roomName;
			cout << "Enter device ID to move: ";	cin >> id;
			cout << "Enter room name to place: ";	cin >> roomName;

			auto device = manager.SearchDevice(id);
			if (device == nullptr) {
				cout << "Device not found.\n";
				break;
			}

			if (manager.GetRoomNameByDeviceID(id) == "Device not found in any room")
				cout << "Device not found in any room.\n";
			else {
				cout << "Device found in room: " << manager.GetRoomNameByDeviceID(id) << endl;
				auto room = manager.SearchRoom(manager.GetRoomNameByDeviceID(id));
				if (room)
					manager.RemoveDeviceByID(id);
				manager.AddDeviceToRoom(device, roomName);
			}

			break;
		}
		case 7: {
			string roomName;
			int id;
			cout << "Enter room name: ";			cin >> roomName;
			cout << "Enter device ID to remove: ";	cin >> id;

			auto room = manager.SearchRoom(roomName);
			if (room) {
				if (room->RemoveDevice(id))
					cout << "Device removed successfully.\n";
				else
					cout << "Device not found in this room.\n";
			}
			else
				cout << "Room not found.\n";

			break;
		}
		case 8: {
			string roomName;
			cout << "Enter room name: ";	cin >> roomName;

			auto room = manager.SearchRoom(roomName);
			if (room)
				room->ListDevicesDetails();
			else
				cout << "Room not found.\n";

			break;
		}
		case 9: {
			string roomName;
			cout << "Enter room name to duplicate: ";	cin >> roomName;

			manager.DuplicateRoom(roomName);
			break;
		}
		case 10: {
			manager.ViewAllRooms();
			break;
		}
		case 11: {
			string filename;
			cout << "Enter filename to load from: ";	cin >> filename;

			manager.LoadFromFile(filename);
			break;
		}
		case 12:
			cout << "Exiting system. Goodbye!\n";
			return 0;
		default:
			cout << "Invalid choice. Try again.\n";
		}
		cout << "\n";
	} while (choice != 0);
}