#include "SmartWashingMachine.h"

shared_ptr<SmartDevice> SmartWashingMachine::Clone() const { return make_shared<SmartWashingMachine>(*this); }

SmartWashingMachine::SmartWashingMachine(int id, const string& name, const string& manufacturer,
	const string& cycle, int dur, int capacity)
	: SmartDevice(id, name, manufacturer), washCycle(cycle), duration(dur), loadCapacity(capacity) {}

void SmartWashingMachine::InteractionEvent() const {
	if (status)
		cout << "Washing Machine is running. Cycle: " << washCycle << ", Duration: " << duration << " mins, Capacity: "
		<< loadCapacity << " kg.\n";
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