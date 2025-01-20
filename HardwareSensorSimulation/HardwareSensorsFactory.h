#pragma once
#include <memory>
#include "IHSensor.h"
#include "../DataHelper/ObjectType.h"
#include "../DataHelper/MessageQueue.h"
 
class HardwareSensorsFactory {
public:
	//callback function for creating objects
	static std::unique_ptr<IHDevice> CreateObject(SensorData& sensorData);

private:
	HardwareSensorsFactory() {}
	~HardwareSensorsFactory(){}
	HardwareSensorsFactory(const HardwareSensorsFactory& obj) {}
};