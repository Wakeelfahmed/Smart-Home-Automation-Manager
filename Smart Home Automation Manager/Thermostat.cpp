#include "Thermostat.h"

Thermostat::Thermostat(int id, const string& name, const string& manufacturer, float temp)
	: SmartDevice(id, name, manufacturer), TemperatureSet(temp) {}

void Thermostat::InteractionEvent() const {

	std::cout << "Temperature: 25° C" << std::endl;

	if (status)
		cout << "Thermostat is set to " << TemperatureSet << "\u00B0 C\n";
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