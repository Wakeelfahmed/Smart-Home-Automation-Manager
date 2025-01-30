#include "SmartWashingMachine.h"

shared_ptr<SmartDevice> SmartWashingMachine::Clone() const { return make_shared<SmartWashingMachine>(*this); }

SmartWashingMachine::SmartWashingMachine(int id, const string& name, const string& manufacturer, const string& cycle, int dur, int capacity)
	: SmartDevice(id, name, manufacturer), washCycle(cycle), duration(dur), loadCapacity(capacity) {}

void SmartWashingMachine::InteractionEvent() {
	int choice;
	if (status) {
		cout << "Washing Machine is running. Cycle: " << washCycle << ", Duration: " << duration << " mins, Capacity: " << loadCapacity << " kg.\n";
		cout << "1. Stop Washing Machine\t2. Change Wash Cycle/Duration\n";
		cin >> choice;
		if (choice == 1)
			status = false;
		else if (choice == 2) {
			string cycle;
			int dur;
			cout << "Enter new wash cycle: ";
			cin >> cycle;
			cout << "Enter duration: ";
			cin >> dur;
			SetWashCycle(cycle, dur);
		}
	}
	else
		cout << "Washing Machine is inactive.\n";
}

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

void SmartWashingMachine::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Wash Cycle: " << washCycle << "\tDuration: " << duration << " mins\tLoad Capacity: " << loadCapacity << " kg\n";
}