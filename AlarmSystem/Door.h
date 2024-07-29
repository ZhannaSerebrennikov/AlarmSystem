#pragma once
#include <memory>
#include <mutex>

#include "ISensor.h"
#include "../DataHelper/ObjectType.h"

class Door : public ISensor {
public:
	Door(SensorData sensorData);
	SensorData GetSensorData() const;
	void SetSensorData(SensorData data);

private:
	SensorData m_sensorData;
	std::atomic<bool> stop;
};