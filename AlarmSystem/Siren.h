#pragma once
#include "ISensor.h"
#include "../DataHelper/ObjectType.h"

class Siren : public ISensor {
public:
	Siren(SensorData);
	SensorData GetSensorData() const;
	void SetSensorData(SensorData data);

private:
	SensorData m_sensorData;
};