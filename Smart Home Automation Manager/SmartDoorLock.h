#ifndef SMARTDOORLOCK_H
#define SMARTDOORLOCK_H

#include "SmartDevice.h"

// SmartDoorLock class inherits from SmartDevice
class SmartDoorLock : public SmartDevice {
	string authMethod;	// Authentication method (e.g., Keypad, Biometric, Remote Control)

	// Creates a copy of the SmartDoorLock object
	shared_ptr<SmartDevice> Clone() const override;

public:
	// Constructor to initialize a smart door lock with an authentication method
	SmartDoorLock(int id, const string& name, const string& manufacturer,
		const string& auth = "Keypad");

	// Locks the door
	void Lock();

	// Unlocks the door
	void Unlock();

	// Handles interaction events specific to the smart door lock
	void InteractionEvent() override;

	// Displays detailed information about the smart door lock
	void ViewInfo() const override;

	// Sets the authentication method for the lock
	void SetAuthMethod(const string& method);
};

#endif // SMARTDOORLOCK_H
