#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "SmartDevice.h"
using namespace std;

class SecurityCamera : public SmartDevice {
	string CameraRes;
	string powerSource;

	shared_ptr<SmartDevice> Clone() const override;

public:
	SecurityCamera(int id, const string& name, const string& manufacturer, const string& quality, const string& power);
	void InteractionEvent() const override;
	void ViewInfo() const override;
};

#endif
