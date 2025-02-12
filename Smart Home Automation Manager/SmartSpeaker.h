#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H

#include "SmartDevice.h"
using namespace std;

// SmartSpeaker class inherits from SmartDevice
class SmartSpeaker : public SmartDevice {
	int volumeLevel;	// Volume level of the speaker (0-100)

	// Creates a copy of the SmartSpeaker object
	shared_ptr<SmartDevice> Clone() const override;

public:
	// Constructor to initialize a smart speaker with a volume level
	SmartSpeaker(int id, const string& name, const string& manufacturer,
		int volume = 50);

	// Handles interaction events specific to the smart speaker
	void InteractionEvent() override;

	// Sets the volume level of the speaker
	void SetVolumeLevel(int level);

	// Displays detailed information about the smart speaker
	void ViewInfo() const override;
};

#endif // SMARTSPEAKER_H
