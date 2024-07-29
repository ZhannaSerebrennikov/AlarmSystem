#include "Siren.h"

Siren::Siren(SensorData sensorData) : m_sensorData(sensorData){}

SensorData Siren::GetSensorData() const
{
	return m_sensorData;
}


void Siren::SetSensorData(SensorData data)
{
	m_sensorData = data;
}