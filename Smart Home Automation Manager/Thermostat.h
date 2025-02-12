#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
using namespace std;

// Thermostat class inherits from SmartDevice
class Thermostat : public SmartDevice {
	float TemperatureSet;	// Target temperature setting in degrees Celsius

	// Creates a copy of the Thermostat object
	shared_ptr<SmartDevice> Clone() const override;

public:
	// Constructor to initialize a thermostat with a default temperature setting
	Thermostat(int id, const string& name, const string& manufacturer, float temp = 22.0f);

	// Handles interaction events specific to the thermostat
	void InteractionEvent() override;

	// Sets the target temperature
	void SetTargetTemperature(float temp);

	// Displays detailed information about the thermostat
	void ViewInfo() const override;
};

#endif // THERMOSTAT_H
