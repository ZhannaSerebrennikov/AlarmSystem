#pragma once
#include "../DataHelper/ObjectType.h"
#include "IObserver.h"
#include <vector>

class IDevice {
public:
	virtual SensorData GetSensorData() const = 0;
	virtual void SetSensorData(SensorData data) = 0;
	virtual ~IDevice() = default;
};