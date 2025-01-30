#include "SmartSpeaker.h"

SmartSpeaker::SmartSpeaker(int id, const string& name, const string& manufacturer, int volume)
	: SmartDevice(id, name, manufacturer), volumeLevel(volume) {}

shared_ptr<SmartDevice> SmartSpeaker::Clone() const { return make_shared<SmartSpeaker>(*this); }

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

void SmartSpeaker::SetVolumeLevel(int level) {
	if (status && level >= 0 && level <= 100) {
		volumeLevel = level;
		cout << "Volume set to " << volumeLevel << '\n';
	}
	else
		cout << "Invalid volume level or speaker is inactive.\n";
}

void SmartSpeaker::ViewInfo() const {
	SmartDevice::ViewInfo();
	cout << "Volume Level: " << volumeLevel << '\n';
}