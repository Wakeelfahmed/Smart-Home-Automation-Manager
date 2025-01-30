#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
using namespace std;

class Thermostat : public SmartDevice {
	float TemperatureSet;

	shared_ptr<SmartDevice> Clone() const override;
public:
	Thermostat(int id, const string& name, const string& manufacturer, float temp = 22.0f);
	void InteractionEvent() override;
	void SetTargetTemperature(float temp);
	void ViewInfo() const override;
};

#endif 
