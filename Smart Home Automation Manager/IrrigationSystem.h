#ifndef IRRIGATIONSYSTEM_H
#define IRRIGATIONSYSTEM_H

#include "SmartDevice.h"

// IrrigationSystem class inherits from SmartDevice
class IrrigationSystem : public SmartDevice {
	int wateringDuration;	// Watering duration in minutes
	string schedule;		// Watering schedule, e.g., "8:00 AM, Daily"
	float waterUsage;		// Water usage in liters

	// Clones the current IrrigationSystem object
	shared_ptr<SmartDevice> Clone() const override;
public:
	// Constructor to initialize the irrigation system with default or provided values
	IrrigationSystem(int id, const string& name, const string& manufacturer, int duration = 30, const string& sched = "6:00 AM, Daily", float usage = 0);

	// Sets the watering duration
	void SetWateringDuration(int duration);

	// Sets the watering schedule
	void SetSchedule(const string& sched);

	// Checks and displays water usage
	void CheckWaterUsage() const;

	// Handles interaction events
	void InteractionEvent() override;

	// Displays device information
	void ViewInfo() const override;
};

#endif // IRRIGATIONSYSTEM_H
