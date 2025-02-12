#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "SmartDevice.h"
using namespace std;

// SecurityCamera class inherits from SmartDevice
class SecurityCamera : public SmartDevice {
	string CameraRes;	 // Camera resolution (e.g., "1080p", "4K")
	string powerSource;	 // Power source type (e.g., "Battery", "Wired")

	// Creates a copy of the SecurityCamera object
	shared_ptr<SmartDevice> Clone() const override;

public:
	// Constructor to initialize a security camera with given attributes
	SecurityCamera(int id, const string& name, const string& manufacturer,
		const string& quality, const string& power);

	// Handles interaction events specific to the security camera
	void InteractionEvent() override;

	// Displays detailed information about the security camera
	void ViewInfo() const override;
};

#endif // SECURITYCAMERA_H
