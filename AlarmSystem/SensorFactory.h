#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include "ISensor.h"
#include "IDevice.h"
#include "../DataHelper/ObjectType.h"

class SensorFactory {
public:
	//callback function for creating objects
	static std::unique_ptr<ISensor> CreateSensorObject(SensorData& sensorData);
	static std::unique_ptr<IDevice> CreateDeviceObject(SensorData& sensorData);

private:
	SensorFactory(){}
	~SensorFactory(){}
	SensorFactory(const SensorFactory& obj){}
};