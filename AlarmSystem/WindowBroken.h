#pragma once
#include "ISensor.h"
#include "../DataHelper/ObjectType.h"

class WindowBroken : public ISensor {
public:
	WindowBroken(SensorData sensorData);
	SensorData GetSensorData() const;
	void SetSensorData(SensorData data);

private:
	SensorData m_sensorData;
};
