#include "SmartSpeaker.h"

// Constructor to initialize the SmartSpeaker with the given id, name, manufacturer, and volume
SmartSpeaker::SmartSpeaker(int id, const string& name, const string& manufacturer, int volume)
	: SmartDevice(id, name, manufacturer), volumeLevel(volume) {}

// Clone method to create a copy of the SmartSpeaker object
shared_ptr<SmartDevice> SmartSpeaker::Clone() const { return make_shared<SmartSpeaker>(*this); }

// InteractionEvent method to allow user to interact with the SmartSpeaker and adjust volume
void SmartSpeaker::InteractionEvent() {
	if (!status) {
		cout << "Smart Speaker is inactive.\n";
		return;
	}
	int vol;
	cout << "Adjust volume level: ";
	cin >> vol;
	SetVolumeLevel(vol);
}

// SetVolumeLevel method to change the volume of the speaker. Ensures volume is between 0 and 100
void SmartSpeaker::SetVolumeLevel(int level) {
	if (status && level >= 0 && level <= 100) {
		volumeLevel = level;
		cout << "Volume set to " << volumeLevel << '\n';
	}
	else
		cout << "Invalid volume level or speaker is inactive.\n";
}

// ViewInfo method to display the SmartSpeaker's current state (volume level)
void SmartSpeaker::ViewInfo() const {
	SmartDevice::ViewInfo();	// Calls the base class ViewInfo method
	cout << "Volume Level: " << volumeLevel << '\n';
}