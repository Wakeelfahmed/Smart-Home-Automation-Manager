#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>
#include <iostream>
#include "SmartDevice.h"

class Room {
private:
    std::string name;
    std::vector<std::shared_ptr<SmartDevice>> devices;

public:
    Room(const std::string& roomName);

    const std::string& GetName() const;

    void AddDevice(std::shared_ptr<SmartDevice> device);

    void RemoveDevice(int id);

    void ListDevices() const;

    void ListDevicesDetails() const;

    void ActivateAllDevices();

    void DeactivateAllDevices();

    const std::vector<std::shared_ptr<SmartDevice>>& GetDevices() const;
};

#endif // ROOM_H
