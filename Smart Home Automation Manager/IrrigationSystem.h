#ifndef IRRIGATIONSYSTEM_H
#define IRRIGATIONSYSTEM_H

#include "SmartDevice.h"

class IrrigationSystem : public SmartDevice {
	int wateringDuration;	// in minutes
	string schedule;		// e.g., "8:00 AM, Daily"
	float waterUsage;		// in liters

	shared_ptr<SmartDevice> Clone() const override;
public:
	IrrigationSystem(int id, const string& name, const string& manufacturer, int duration = 30, const string& sched = "6:00 AM, Daily", float usage = 0);
	void SetWateringDuration(int duration);
	void SetSchedule(const string& sched);
	void CheckWaterUsage() const;
	void InteractionEvent() override;
	void ViewInfo() const override;
};

#endif // IRRIGATIONSYSTEM_H