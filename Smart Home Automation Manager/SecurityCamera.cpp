#include "SecurityCamera.h"

SecurityCamera::SecurityCamera(int id, const string& name, const string& manufacturer, const string& quality, const string& power) 
	: SmartDevice(id, name, manufacturer), CameraRes(quality), powerSource(power) {}

shared_ptr<SmartDevice> SecurityCamera::Clone() const { return make_shared<SecurityCamera>(*this); }

void SecurityCamera::InteractionEvent() {
	if (status) {
		int choice;
		cout << "Now viewing camera: " << name << " (" << CameraRes << " quality)\n";
		cout << "Press 1. Rotate Camera left\tPress 2. Rotate Camera right\n";
		cin >> choice;
		if (choice == 1)
			cout << "Camera rotated left.\n";
		else if (choice == 2)
			cout << "Camera rotated right.\n";
		else
			cout << "Invalid input.\n";
	}
	else
		cout << "Camera is inactive.\n";
}

void SecurityCamera::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Camera Quality: " << CameraRes << "\tPower Source: " << powerSource << '\n';
}