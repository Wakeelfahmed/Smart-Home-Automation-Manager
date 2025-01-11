#include "SmartLight.h"

SmartLight::SmartLight(int id, const string& name, const string& manufacturer, int brightness, const string& color)
	: SmartDevice(id, name, manufacturer), brightnessLevel(brightness), colorType(color) {}

shared_ptr<SmartDevice> SmartLight::Clone() const { return make_shared<SmartLight>(*this); }

void SmartLight::InteractionEvent() const {
	if (status)
		cout << "Smart Light brightness: " << brightnessLevel
		<< ", color: " << colorType << '\n';
	else
		cout << "Smart Light is inactive.\n";
}

void SmartLight::SetBrightness(int level) {
	if (status && level >= 0 && level <= 100) {
		brightnessLevel = level;
		cout << "Brightness set to " << brightnessLevel << '\n';
	}
	else 
		cout << "Invalid brightness level or light is inactive.\n";
}

void SmartLight::SetColor(const string& color) {
	if (status && colorType == "RGB" || status && colorType == "Warm" || status && colorType == "Cool" || status && colorType == "White") {
		colorType = color;
		cout << "Color set to " << colorType << '\n';
	}
	else 
		cout << "Light does not support color change or is inactive.\n";
}

void SmartLight::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Brightness Level: " << brightnessLevel << "\tColor Type: " << colorType << '\n';
}