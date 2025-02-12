#include "SecurityCamera.h"

// Constructor to initialize a SecurityCamera object with specific values
SecurityCamera::SecurityCamera(int id, const string& name, const string& manufacturer, const string& quality, const string& power) 
	: SmartDevice(id, name, manufacturer), CameraRes(quality), powerSource(power) {}

// Creates a deep copy of the SecurityCamera object
shared_ptr<SmartDevice> SecurityCamera::Clone() const { return make_shared<SecurityCamera>(*this); }

// Handles user interaction with the security camera, allowing camera rotation
void SecurityCamera::InteractionEvent() {
	if (status) {
		int choice;
		cout << "Now viewing camera: " << name << " (" << CameraRes << " quality)\n";
		cout << "Press 1. Rotate Camera left\tPress 2. Rotate Camera right\n";
		cin >> choice;
		if (choice == 1)
			cout << "Camera rotated left.\n";	// Rotates camera left
		else if (choice == 2)
			cout << "Camera rotated right.\n";	// Rotates camera right
		else
			cout << "Invalid input.\n";
	}
	else
		cout << "Camera is inactive.\n";
}

// Displays detailed information about the security camera
void SecurityCamera::ViewInfo() const {
	SmartDevice::ViewInfo();	// Calls the base class ViewInfo method
	cout << "Camera Quality: " << CameraRes << "\tPower Source: " << powerSource << '\n';
}