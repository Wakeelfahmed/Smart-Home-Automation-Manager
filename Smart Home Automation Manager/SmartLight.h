#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include "SmartDevice.h"
using namespace std;

// SmartLight class inherits from SmartDevice
class SmartLight : public SmartDevice {
	int brightnessLevel;	// Brightness level of the light (0-100)
	string colorType;		// Color type of the light (e.g., "Warm White", "Cool White", "RGB")

	// Creates a copy of the SmartLight object
	shared_ptr<SmartDevice> Clone() const override;

public:
	// Constructor to initialize a smart light with brightness and color type
	SmartLight(int id, const string& name, const string& manufacturer,
		int brightness = 50, const string& color = "Warm White");

	// Handles interaction events specific to the smart light
	void InteractionEvent() override;

	// Sets the brightness level of the light
	void SetBrightness(int level);

	// Sets the color type of the light
	void SetColor(const string& color);

	// Displays detailed information about the smart light
	void ViewInfo() const override;
};

#endif // SMARTLIGHT_H
