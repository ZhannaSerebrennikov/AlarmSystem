#include "Door.h"

Door::Door(SensorData sensorData) : m_sensorData(sensorData) {}

SensorData Door::GetSensorData() const
{
	return m_sensorData;
}

void Door::SetSensorData(SensorData data)
{
	m_sensorData = data;
}