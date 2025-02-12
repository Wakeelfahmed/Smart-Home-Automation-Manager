#include "SmartWashingMachine.h"

// Clone method to create a copy of the SmartWashingMachine object
SmartWashingMachine::SmartWashingMachine(int id, const string& name, const string& manufacturer, const string& cycle, int dur, int capacity)
	: SmartDevice(id, name, manufacturer), washCycle(cycle), duration(dur), loadCapacity(capacity) {}

// Clone method to create a copy of the SmartWashingMachine object
shared_ptr<SmartDevice> SmartWashingMachine::Clone() const { return make_shared<SmartWashingMachine>(*this); }

// InteractionEvent method to allow user to interact with the SmartWashingMachine
void SmartWashingMachine::InteractionEvent() {
	int choice;
	if (status) {
		cout << "Washing Machine is running. Cycle: " << washCycle << ", Duration: " << duration << " mins, Capacity: " << loadCapacity << " kg.\n";
		cout << "1. Stop Washing Machine\t2. Change Wash Cycle/Duration\n";
		cin >> choice;
		if (choice == 1)
			status = false;	// Stop the washing machine
		else if (choice == 2) {
			string cycle;
			int dur;
			cout << "Enter new wash cycle: ";
			cin >> cycle;
			cout << "Enter duration: ";
			cin >> dur;
			SetWashCycle(cycle, dur);	// Change the wash cycle and duration
		}
	}
	else
		cout << "Washing Machine is inactive.\n";
}

// SetWashCycle method to change the wash cycle and duration when the machine is active
void SmartWashingMachine::SetWashCycle(const string& cycle, int dur) {
	if (status) {
		washCycle = cycle;
		duration = dur;
		cout << "Wash cycle set to " << washCycle << " for " << duration << " minutes.\n";
	}
	else {
		cout << "Washing Machine is inactive. Cannot set wash cycle.\n";
	}
}

// ViewInfo method to display the SmartWashingMachine's current state (cycle, duration, and capacity)
void SmartWashingMachine::ViewInfo() const {
	SmartDevice::ViewInfo();	// Calls the base class ViewInfo method
	cout << "Wash Cycle: " << washCycle << "\tDuration: " << duration << " mins\tLoad Capacity: " << loadCapacity << " kg\n";
}