#include "Thermostat.h"
#include <windows.h>	// For UTF-8 support

// Constructor for Thermostat class to initialize id, name, manufacturer, and target temperature
Thermostat::Thermostat(int id, const string& name, const string& manufacturer, float temp)
	: SmartDevice(id, name, manufacturer), TemperatureSet(temp) {}

// Clone method for creating a deep copy of the Thermostat object
shared_ptr<SmartDevice> Thermostat::Clone() const { return make_shared<Thermostat>(*this); } // Copy constructor for deep copy

// InteractionEvent method to allow user interaction with the thermostat
void Thermostat::InteractionEvent() {
	int choice;
	if (status) {
		cout << "Thermostat is set to " << TemperatureSet << "°C\n";
		cout << "Press 1. Set Target Temperature\n";
		cin >> choice;
		if (choice == 1) {
			float temp;
			cout << "Enter target temperature: ";	cin >> temp;
			SetTargetTemperature(temp);	// Calls SetTargetTemperature to update the temperature
		}
		else
			cout << "Invalid input.\n";
	}
	else
		cout << "Thermostat is inactive.\n";
}

// SetTargetTemperature method to set the target temperature if the thermostat is active
void Thermostat::SetTargetTemperature(float temp) {
	if (status) {
		TemperatureSet = temp;
		cout << "Target temperature set to " << TemperatureSet << "°C\n";
	}
	else
		cout << "Thermostat is inactive.\n";
}

// ViewInfo method to display the current state of the thermostat, including the target temperature
void Thermostat::ViewInfo() const {
	SmartDevice::ViewInfo();	// Calls the base class ViewInfo method
	cout << "Target Temperature: " << TemperatureSet << "°C\n";
}