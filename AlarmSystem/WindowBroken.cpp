#include "WindowBroken.h"

WindowBroken::WindowBroken(SensorData sensorData) : m_sensorData(sensorData) {}

SensorData WindowBroken::GetSensorData() const
{
	return m_sensorData;
}


void WindowBroken::SetSensorData(SensorData data)
{
	m_sensorData = data;
}