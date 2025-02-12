#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <string>
#include <iostream>
using namespace std;

// Base class representing a smart device
class SmartDevice {
protected:
	int id;					// Unique identifier for the device
	string name;			// Name of the smart device
	string manufacturer;	// Manufacturer of the device
	bool status;			// Device status: true = active, false = inactive

public:
	// Pure virtual method for cloning a smart device (must be implemented by derived classes)
	virtual shared_ptr<SmartDevice> Clone() const = 0;

	// Constructor to initialize a smart device
	SmartDevice(int id, const string& name, const string& manufacturer);

	// Virtual destructor for proper cleanup of derived classes
	virtual ~SmartDevice();

	// Pure virtual method for handling device-specific interactions
	virtual void InteractionEvent() = 0;

	// Activates the smart device
	void Activate();

	// Deactivates the smart device
	void Deactivate();

	// Returns the current status of the device (true = active, false = inactive)
	bool GetStatus() const;

	// Displays device information (can be overridden by derived classes)
	virtual void ViewInfo() const;

	// Checks if the device is connected (can be overridden by derived classes)
	virtual bool CheckConnection() const;

	// Returns the device ID
	int GetID() const;

	// Sets a new ID for the device
	void SetID(int id);

	// Sets a new name for the device
	void SetName(const string& name);

	// Returns the name of the device
	const string& GetName() const;
};

#endif // SMARTDEVICE_H