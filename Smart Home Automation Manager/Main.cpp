#include <iostream>
#include <windows.h>	// For UTF-8 support & the file be saved as UTF-8 format

#include "SmartHomeManager.h"
using namespace std;

int main() {
	SmartHomeManager manager;

	// Porch
	manager.AddDeviceToRoom(make_shared<SecurityCamera>(1, "Front Door Camera", "CamCorp", "1080p", "Battery"), "Porch");
	manager.AddDeviceToRoom(make_shared<SmartLight>(2, "Porch Light", "Lightify", 100, "Warm White"), "Porch");
	manager.AddDeviceToRoom(make_shared<SmartDoorLock>(3, "Main Door Lock", "SecureHome", "Biometric"), "Porch");

	// Living Room
	manager.AddDeviceToRoom(make_shared<Thermostat>(4, "Living Room Thermostat", "ThermoPro"), "Living");
	manager.AddDeviceToRoom(make_shared<SmartSpeaker>(5, "Living Room Speaker", "SoundBlast", 80), "Living");
	manager.AddDeviceToRoom(make_shared<SmartLight>(6, "Living Room Light", "Lightify", 75, "Cool White"), "Living");

	// Kitchen
	manager.AddDeviceToRoom(make_shared<SmartSpeaker>(7, "Kitchen Speaker", "SoundBlast", 70), "Kitchen");
	manager.AddDeviceToRoom(make_shared<SmartLight>(8, "Kitchen Light", "Lightify", 85, "Neutral White"), "Kitchen");

	// Bedroom
	manager.AddDeviceToRoom(make_shared<SmartLight>(9, "Bedroom Light", "Lightify", 70, "RGB"), "Bedroom");
	manager.AddDeviceToRoom(make_shared<Thermostat>(10, "Bedroom Thermostat", "ThermoPro"), "Bedroom");
	manager.AddDeviceToRoom(make_shared<SmartSpeaker>(11, "Bedroom Speaker", "SoundBlast", 60), "Bedroom");

	// Garden
	manager.AddDeviceToRoom(make_shared<IrrigationSystem>(12, "Garden Irrigation System", "GreenTech"), "Garden");
	manager.AddDeviceToRoom(make_shared<SmartLight>(13, "Garden Light", "Lightify", 50, "Outdoor RGB"), "Garden");

	// Laundry Room
	manager.AddDeviceToRoom(make_shared<SmartWashingMachine>(14, "Laundry Washer", "WashTech", "Quick Wash", 45, 8), "Laundry");
	manager.AddDeviceToRoom(make_shared<SmartLight>(15, "Laundry Room Light", "Lightify", 60, "Neutral White"), "Laundry");

	// Garage
	manager.AddDeviceToRoom(make_shared<SecurityCamera>(16, "Garage Camera", "CamCorp", "720p", "Wired"), "Garage");
	manager.AddDeviceToRoom(make_shared<SmartDoorLock>(17, "Garage Door Lock", "SecureHome", "Keypad"), "Garage");
	manager.AddDeviceToRoom(make_shared<SmartLight>(18, "Garage Light", "Lightify", 90, "Cool White"), "Garage");

	// Bathroom
	manager.AddDeviceToRoom(make_shared<Thermostat>(19, "Bathroom Thermostat", "ThermoPro"), "Bathroom");
	manager.AddDeviceToRoom(make_shared<SmartLight>(20, "Bathroom Light", "Lightify", 75, "Warm White"), "Bathroom");

	SetConsoleOutputCP(CP_UTF8); // Set console code page to UTF-8 to display 

	cout << "Temperature: 25° C" << endl;

	short choice;
	do {
		cout << "=== Smart Home Management System ===\n"
			<< "1. Add a new device\t"
			<< "2. Search for a device\t"
			<< "3. Activate all devices in a room\t"
			<< "4. Deactivate all devices in a room\n"
			<< "5. Create a room\t"
			<< "6. Add device to room\t"
			<< "7. Remove device from room\t\t"
			<< "8. List devices in a room\n"
			<< "9. Duplicate a room\t"
			<< "10. View all rooms\t"
			<< "11. Load devices and rooms from file\n"
			<< "12. Exit\n";
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Enter device type (1: Light, 2: Thermostat, 3: Door Lock, 4: Camera, 5: Speaker): ";
			short type;
			cin >> type;

			int id;
			string name, Mname;
			cout << "Enter device ID: ";
			cin >> id;
			cout << "Enter device name: ";
			cin.ignore();
			getline(cin, name);
			cout << "Enter device Manufacturer: ";
			cin >> Mname;

			shared_ptr<SmartDevice> device;
			if (type == 1) {
				device = make_shared<SmartLight>(id, name, Mname);
			}
			else if (type == 2) {
				device = make_shared<Thermostat>(id, name, Mname);
			}
			else if (type == 3) {
				string authMethod;
				cout << "Enter authentication method: ";
				cin >> authMethod;
				device = make_shared<SmartDoorLock>(id, name, Mname, authMethod);
			}
			else if (type == 4) {
				string res, power;
				cout << "Enter camera resolution: ";
				cin >> res;
				cout << "Enter power source: ";
				cin >> power;
				device = make_shared<SecurityCamera>(id, name, Mname, res, power);
			}
			else if (type == 5) {
				int volume;
				cout << "Enter volume level: ";
				cin >> volume;
				device = make_shared<SmartSpeaker>(id, name, Mname, volume);
			}
			else {
				cout << "Invalid device type.\n";
				break;
			}

			string roomName;
			cout << "Enter room name to add the device: ";
			getline(cin, roomName);

			manager.AddDeviceToRoom(device, roomName);
			break;
		}
		case 2: {
			int id;
			cout << "Enter device ID to search: ";
			cin >> id;

			auto device = manager.SearchDevice(id);
			if (device) {
				device->ViewInfo();
				cout << "Select an action:\n"
					<< "1. Activate\t"
					<< "2. Deactivate\n"
					<< "3. Check connection\t"
					<< "4. Simulate interaction\n";
				short action;
				cin >> action;

				switch (action) {
				case 1: device->Activate(); break;
				case 2: device->Deactivate(); break;
				case 3: device->CheckConnection(); break;
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
			cout << "Enter room name: ";
			cin.ignore();
			getline(cin, roomName);

			auto room = manager.SearchRoom(roomName);
			if (room)
				room->ActivateAllDevices();
			else
				cout << "Room not found.\n";

			break;
		}
		case 4: {
			string roomName;
			cout << "Enter room name: ";
			cin.ignore();
			getline(cin, roomName);

			auto room = manager.SearchRoom(roomName);
			if (room)
				room->DeactivateAllDevices();
			else
				cout << "Room not found.\n";

			break;
		}
		case 5: {
			string roomName;
			cout << "Enter room name: ";
			cin.ignore();
			getline(cin, roomName);

			auto room = make_shared<Room>(roomName);
			manager.AddDeviceToRoom(nullptr, roomName); // Create room without devices
			break;
		}
		case 6: {
			int id;
			string roomName;
			cout << "Enter device ID: ";
			cin >> id;
			cout << "Enter room name: ";
			cin.ignore();
			getline(cin, roomName);

			auto device = manager.SearchDevice(id);
			if (device)
				manager.AddDeviceToRoom(device, roomName);
			else
				cout << "Device not found.\n";

			break;
		}
		case 7: {
			string roomName;
			int id;
			cout << "Enter room name: ";
			cin.ignore();
			getline(cin, roomName);
			cout << "Enter device ID to remove: ";
			cin >> id;

			auto room = manager.SearchRoom(roomName); // Implement SearchRoom in manager
			if (room)
				room->RemoveDevice(id);
			else
				cout << "Room not found.\n";

			break;
		}
		case 8: {
			string roomName;
			cout << "Enter room name: ";
			cin.ignore();
			getline(cin, roomName);

			shared_ptr<Room> room = manager.SearchRoom(roomName);
			if (room)
				room->ListDevicesDetails();
			else
				cout << "Room not found.\n";

			break;
		}
		case 9: {
			string roomName;
			cout << "Enter room name to duplicate: ";
			cin.ignore();
			getline(cin, roomName);

			manager.DuplicateRoom(roomName);
			break;
		}
		case 10: {
			manager.ViewAllRooms();
			break;
		}
		case 11: {
			string filename;
			cout << "Enter filename to load from: ";
			cin >> filename;

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