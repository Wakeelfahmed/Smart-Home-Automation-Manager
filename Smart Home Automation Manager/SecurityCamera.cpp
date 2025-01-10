#include "SecurityCamera.h"

SecurityCamera::SecurityCamera(int id, const string& name, const string& manufacturer, const string& quality, const string& power) 
	: SmartDevice(id, name, manufacturer), CameraRes(quality), powerSource(power) {}

void SecurityCamera::InteractionEvent() const {
	if (status)
		cout << "Now viewing camera: " << name << " (" << CameraRes << " quality)\n";
	else
		cout << "Camera is inactive.\n";
}

void SecurityCamera::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Camera Quality: " << CameraRes << "\tPower Source: " << powerSource << '\n';
}