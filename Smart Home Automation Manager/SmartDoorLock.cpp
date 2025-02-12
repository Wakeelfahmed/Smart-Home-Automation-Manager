#include "SmartDoorLock.h"

// Constructor to initialize the SmartDoorLock with the given id, name, manufacturer, and authentication method
SmartDoorLock::SmartDoorLock(int id, const string& name, const string& manufacturer, const string& auth)
	: SmartDevice(id, name, manufacturer), authMethod(auth) {}

// Clone method for creating a copy of the SmartDoorLock object
shared_ptr<SmartDevice> SmartDoorLock::Clone() const { return make_shared<SmartDoorLock>(*this); }

// Locks the door lock (sets status to true). If it's already locked, it displays a message.
void SmartDoorLock::Lock() {
	if (status)
		cout << name << " is already Locked.\n";
	else
		cout << name << " is now Locked.\n";
	status = true;
}

// Unlocks the door lock (sets status to false). If it's already unlocked, it displays a message.
void SmartDoorLock::Unlock() {
	if (!status)
		cout << name << " is already Unlocked.\n";
	else
		cout << name << "Door lock is now Unlocked.\n";
	status = false;
}

// Handles interaction with the user (locking or unlocking the door lock).
void SmartDoorLock::InteractionEvent() {
	cout << name << ". Authentication Method: " << authMethod << '\n';
	int input;
	cout << "Press to 1. Lock\tPress 2. Unlock\n";
	cin >> input;
	if (input == 1)
		Lock();
	else if (input == 2)
		Unlock();
	else
		cout << "Invalid input.\n";
}

// Displays the information of the SmartDoorLock, including the authentication method.
void SmartDoorLock::ViewInfo() const {
	SmartDevice::ViewInfo();	// Calls the base class ViewInfo method
	cout << "Authentication Method: " << authMethod << '\n';
}

// Updates the authentication method of the door lock and displays the change.
void SmartDoorLock::SetAuthMethod(const string& method) {
	authMethod = method;
	cout << "Authentication method updated to " << authMethod << '\n';
}