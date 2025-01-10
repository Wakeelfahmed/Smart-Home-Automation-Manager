#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
using namespace std;

class Thermostat : public SmartDevice {
private:
	float TemperatureSet;

public:
	Thermostat(int id, const string& name, const string& manufacturer, float temp = 22.0f);
	void InteractionEvent() const override;
	void SetTargetTemperature(float temp);
	void ViewInfo() const override;
};

#endif 
