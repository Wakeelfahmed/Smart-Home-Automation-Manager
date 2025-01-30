#ifndef SMARTWASHINGMACHINE_H
#define SMARTWASHINGMACHINE_H

#include "SmartDevice.h"

class SmartWashingMachine : public SmartDevice {
	string washCycle;	// "Cotton", "Synthetic", "Quick Wash"
	int duration;		// Duration in minutes
	int loadCapacity;	// Load capacity in kilograms

	shared_ptr<SmartDevice> Clone() const override;
public:
	SmartWashingMachine(int id, const string& name, const string& manufacturer, const string& cycle = "Normal", int dur = 60, int capacity = 7);
	void InteractionEvent() override;
	void SetWashCycle(const string& cycle, int dur);
	void ViewInfo() const override;
};

#endif // SMARTWASHINGMACHINE_H
