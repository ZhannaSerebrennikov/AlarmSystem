#pragma once
#include "ISensor.h"
#include "../DataHelper/ObjectType.h"

class Smoke : public ISensor {
public:
	Smoke(SensorData sensorData);
	SensorData GetSensorData() const;
	void SetSensorData(SensorData data);

private:
	SensorData m_sensorData;
};
