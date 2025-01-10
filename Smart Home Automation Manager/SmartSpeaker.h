#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H

#include "SmartDevice.h"
using namespace std;

class SmartSpeaker : public SmartDevice {
	int volumeLevel;

	shared_ptr<SmartDevice> Clone() const override;
public:
	SmartSpeaker(int id, const string& name, const string& manufacturer, int volume = 50);
	void InteractionEvent() const override;
	void SetVolumeLevel(int level);
	void ViewInfo() const override;
};

#endif 
