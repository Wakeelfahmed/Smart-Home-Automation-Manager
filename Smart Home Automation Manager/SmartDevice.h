#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <string>
#include <iostream>
using namespace std;

class SmartDevice {
protected:
	int id;
	string name;
	string manufacturer;
	bool status; // true = active, false = inactive

public:
	SmartDevice(int id, const string& name, const string& manufacturer);
	virtual ~SmartDevice();
	virtual void InteractionEvent() const = 0;
	void Activate();
	void Deactivate();
	bool GetStatus() const;
	virtual void ViewInfo() const;
	virtual bool CheckConnection() const;
	int GetID() const;
	void SetID(int id);
	void SetName(const string& name);
	const string& GetName() const;
};

#endif