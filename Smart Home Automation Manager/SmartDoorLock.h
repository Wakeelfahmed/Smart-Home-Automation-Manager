#ifndef SMARTDOORLOCK_H
#define SMARTDOORLOCK_H

#include "SmartDevice.h"

class SmartDoorLock : public SmartDevice {
	string authMethod;     // Keypad, Biometric, or Remote Control

	shared_ptr<SmartDevice> Clone() const override;
public:
	SmartDoorLock(int id, const string& name, const string& manufacturer, const string& auth = "Keypad");
	void Lock();
	void Unlock();
	void InteractionEvent() const override;
	void ViewInfo() const override;
	void SetAuthMethod(const string& method);
};

#endif // SMARTDOORLOCK_H
