#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include "SmartDevice.h"
using namespace std;

class SmartLight : public SmartDevice {
private:
	int brightnessLevel;
	string colorType;

public:
	SmartLight(int id, const string& name, const string& manufacturer, int brightness = 50, const string& color = "Warm White");
	void InteractionEvent() const override;
	void SetBrightness(int level);
	void SetColor(const string& color);
	void ViewInfo() const override;
};

#endif
