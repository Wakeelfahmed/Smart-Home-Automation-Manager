#ifndef SMARTWASHINGMACHINE_H
#define SMARTWASHINGMACHINE_H

#include "SmartDevice.h"

// SmartWashingMachine class inherits from SmartDevice
class SmartWashingMachine : public SmartDevice {
	string washCycle;	// Wash cycle type (e.g., "Cotton", "Synthetic", "Quick Wash", "Normal")
	int duration;		// Duration of the wash cycle in minutes
	int loadCapacity;	// Load capacity of the washing machine in kilograms

	// Creates a copy of the SmartWashingMachine object
	shared_ptr<SmartDevice> Clone() const override;

public:
	// Constructor to initialize a smart washing machine with cycle type, duration, and load capacity
	SmartWashingMachine(int id, const string& name, const string& manufacturer,
		const string& cycle = "Normal", int dur = 60, int capacity = 7);

	// Handles interaction events specific to the smart washing machine
	void InteractionEvent() override;

	// Sets the wash cycle type and its duration
	void SetWashCycle(const string& cycle, int dur);

	// Displays detailed information about the smart washing machine
	void ViewInfo() const override;
};

#endif // SMARTWASHINGMACHINE_H
