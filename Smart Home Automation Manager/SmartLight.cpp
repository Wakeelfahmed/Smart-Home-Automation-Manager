#include "SmartLight.h"

SmartLight::SmartLight(int id, const string& name, const string& manufacturer, int brightness, const string& color)
	: SmartDevice(id, name, manufacturer), brightnessLevel(brightness), colorType(color) {}

shared_ptr<SmartDevice> SmartLight::Clone() const { return make_shared<SmartLight>(*this); }

void SmartLight::InteractionEvent() {
	int choice;
	if (status) {
		cout << "Smart Light brightness: " << brightnessLevel << ", color: " << colorType << '\n';
		cout << "Press 1. Set Brightness\nPress 2. Set Color\n";
		cin >> choice;
		if (choice == 1) {
			int level;
			cout << "Enter brightness level: ";
			cin >> level;
			SetBrightness(level);
		}
		else if (choice == 2) {
			string color;
			cout << "Enter color: ";
			cin >> color;
			SetColor(color);
		}
		else
			cout << "Invalid input.\n";
	}
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