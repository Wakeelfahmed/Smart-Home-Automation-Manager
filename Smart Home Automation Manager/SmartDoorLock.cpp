#include "SmartDoorLock.h"

SmartDoorLock::SmartDoorLock(int id, const string& name, const string& manufacturer, const string& auth)
	: SmartDevice(id, name, manufacturer), authMethod(auth) {}

shared_ptr<SmartDevice> SmartDoorLock::Clone() const { return make_shared<SmartDoorLock>(*this); }

void SmartDoorLock::Lock() {
	if (status)
		cout << name << " is already Locked.\n";
	else
		cout << name << " is now Locked.\n";
	status = true;
}

void SmartDoorLock::Unlock() {
	if (!status)
		cout << name << " is already Unlocked.\n";
	else
		cout << name << "Door lock is now Unloaked.\n";
	status = false;
}

void SmartDoorLock::InteractionEvent() const {
	if (status)
		cout << name << ". Authentication Method: " << authMethod << '\n';
	else
		cout << name << " is inactive.\n";
}

void SmartDoorLock::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Current State: " << status << "\tAuthentication Method: " << authMethod << '\n';
}

void SmartDoorLock::SetAuthMethod(const string& method) {
	if (status) {
		authMethod = method;
		cout << "Authentication method updated to " << authMethod << '\n';
	}
	else
		cout << "Door lock is inactive. Activate it to update settings.\n";
}