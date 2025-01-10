#include "Thermostat.h"
#include <windows.h>	// For UTF-8 support

Thermostat::Thermostat(int id, const string& name, const string& manufacturer, float temp)
	: SmartDevice(id, name, manufacturer), TemperatureSet(temp) {}

shared_ptr<SmartDevice> Thermostat::Clone() const { return make_shared<Thermostat>(*this); } // Copy constructor for deep copy

void Thermostat::InteractionEvent() const {
	if (status)
		cout << "Thermostat is set to " << TemperatureSet << "°C\n";
	else
		cout << "Thermostat is inactive.\n";
}

void Thermostat::SetTargetTemperature(float temp) {
	if (status) {
		TemperatureSet = temp;
		cout << "Target temperature set to " << TemperatureSet << "°C\n";
	}
	else
		cout << "Thermostat is inactive.\n";
}

void Thermostat::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Target Temperature: " << TemperatureSet << "°C\n";
}
