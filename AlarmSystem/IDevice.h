#pragma once
#include "../DataHelper/ObjectType.h"
#include "IObserver.h"
#include <vector>

class IDevice {
public:
	virtual SensorData GetSensorData() const = 0;
	virtual const std::vector<std::shared_ptr<IObserver>> GetData() { return {}; }
	virtual ~IDevice() = default;
};