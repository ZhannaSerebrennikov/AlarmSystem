#pragma once
#include "../DataHelper/ObjectType.h"

class ISensor {
public:
	virtual SensorData GetSensorData() const = 0;
	virtual void SetSensorData(SensorData data) = 0;
	virtual ~ISensor() {}
};