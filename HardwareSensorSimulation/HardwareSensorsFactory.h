#pragma once
#include <memory>
#include "IHSensor.h"
#include "../DataHelper/ObjectType.h"
#include "../DataHelper/MessageQueue.h"
 
class HardwareSensorsFactory {
public:
	//callback function for creating objects
	static std::unique_ptr<IHSensor> CreateObject(SensorData& sensorData, MessageQueue& messageQueue);

private:
	HardwareSensorsFactory() {}
	~HardwareSensorsFactory(){}
	HardwareSensorsFactory(const HardwareSensorsFactory& obj) {}
};