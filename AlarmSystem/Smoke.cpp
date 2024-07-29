#include "Smoke.h"

Smoke::Smoke(SensorData sensorData) :m_sensorData(sensorData) {}

SensorData Smoke::GetSensorData() const
{
	return m_sensorData;
}

void Smoke::SetSensorData(SensorData data)
{
	m_sensorData = data;
}