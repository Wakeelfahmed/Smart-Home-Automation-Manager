#include "IrrigationSystem.h"

IrrigationSystem::IrrigationSystem(int id, const string& name, const string& manufacturer,
	int duration, const string& sched, int usage)
	: SmartDevice(id, name, manufacturer), wateringDuration(duration), schedule(sched), waterUsage(usage) {}

shared_ptr<SmartDevice> IrrigationSystem::Clone() const { return make_shared<IrrigationSystem>(*this); }	// Copy constructor for deep copy

void IrrigationSystem::SetWateringDuration(int duration) {
	if (status && duration > 0) {
		wateringDuration = duration;
		cout << "Watering duration set to " << wateringDuration << " minutes.\n";
	}
	else {
		cout << "Invalid duration or system is inactive.\n";
	}
}

void IrrigationSystem::SetSchedule(const string& sched) {
	if (status) {
		schedule = sched;
		cout << "Schedule set to " << schedule << '\n';
	}
	else {
		cout << "System is inactive.\n";
	}
}

void IrrigationSystem::CheckWaterUsage() const {
	if (status) {
		cout << "Water used so far: " << waterUsage << " liters.\n";
	}
	else {
		cout << "System is inactive.\n";
	}
}

void IrrigationSystem::InteractionEvent() const {
	if (status) {
		cout << "Irrigation System is running on schedule: " << schedule
			<< " for " << wateringDuration << " minutes.\n";
	}
	else {
		cout << "Irrigation System is inactive.\n";
	}
}

void IrrigationSystem::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Watering Duration: " << wateringDuration << " minutes\n"
		<< "Schedule: " << schedule << "\n"
		<< "Water Usage: " << waterUsage << " liters\n";
}