#include "KeyPad.h"

KeyPad::KeyPad(SensorData sensorData) : m_sensorData(sensorData)
{

}

SensorData KeyPad::GetSensorData() const
{
	return m_sensorData;
}

void KeyPad::SetSensorData(SensorData data)
{
	SetStatus(data.sensorStatus);
	m_sensorData = data;
}

void KeyPad::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		//NotifyObservers();
	}
}

int KeyPad::GetUserInput()
{
	return m_sensorData.inputOutput;
}