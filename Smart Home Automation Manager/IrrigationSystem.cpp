#include "IrrigationSystem.h"

// Constructor to initialize an IrrigationSystem object with specific values
IrrigationSystem::IrrigationSystem(int id, const string& name, const string& manufacturer, int duration, const string& sched, float usage)
	: SmartDevice(id, name, manufacturer), wateringDuration(duration), schedule(sched), waterUsage(usage) {}

// Creates a deep copy of the IrrigationSystem object
shared_ptr<SmartDevice> IrrigationSystem::Clone() const { return make_shared<IrrigationSystem>(*this); }	// Copy constructor for deep copy

// Sets the watering duration if the system is active and the duration is valid
void IrrigationSystem::SetWateringDuration(int duration) {
	if (status && duration > 0) {
		wateringDuration = duration;
		cout << "Watering duration set to " << wateringDuration << " minutes.\n";
	}
	else {
		cout << "Invalid duration or system is inactive.\n";
	}
}
// Sets the schedule for watering if the system is active
void IrrigationSystem::SetSchedule(const string& sched) {
	if (status) {
		schedule = sched;
		cout << "Schedule set to " << schedule << '\n';
	}
	else {
		cout << "System is inactive.\n";
	}
}

// Displays the total water usage if the system is active
void IrrigationSystem::CheckWaterUsage() const {
	if (status)
		cout << "Water used so far: " << waterUsage << " liters.\n";
	else
		cout << "System is inactive.\n";
}

// Handles user interaction with the irrigation system, allowing stopping, changing schedule, or changing watering duration
void IrrigationSystem::InteractionEvent() {
	int choice;
	if (status) {
		cout << "Irrigation System is running on schedule: " << schedule << " for " << wateringDuration << " minutes.\n";
		cout << "1. Stop Irrigation\t2. Change Schedule\t3. Change Watering Duration\n";
		cin >> choice;
		if (choice == 1)
			status = false;	// Stops the system

		else if (choice == 2) {
			string sched;
			cout << "Enter new schedule: ";		cin >> sched;
			SetSchedule(sched);	// Changes the schedule
		}
		else if (choice == 3) {
			int duration;
			cout << "Enter new watering duration: ";	cin >> duration;
			SetWateringDuration(duration);	// Changes the watering duration
		}
		else
			cout << "Invalid input.\n";
	}
	else
		cout << "Irrigation System is inactive.\n";
}

// Displays detailed information about the irrigation system
void IrrigationSystem::ViewInfo() const {
	SmartDevice::ViewInfo();	// Calls the base class ViewInfo method
	cout << "Watering Duration: " << wateringDuration << " minutes\t" << "Schedule: " << schedule << "\t" << "Water Usage: " << waterUsage << " liters\n";
}