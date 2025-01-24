#include "GUI.h"

GUI::GUI(SensorData sensorData) : m_sensorData(sensorData)
{
	m_sensorData.inputOutput = 0;
}

void GUI::SetActiveAlarms(const std::vector<std::shared_ptr<IObserver>>& activeAlarms)
{
	m_ActiveAlarms = activeAlarms;
}

const std::vector<std::shared_ptr<IObserver>> GUI::GetActiveAlarms()
{
	return m_ActiveAlarms;
}

void GUI::RemoveActiveAlarm(std::string alarmToRemove)
{
	//TODO
}

const std::vector<std::shared_ptr<IObserver>> GUI::GetData()
{
	return GetActiveAlarms();
}

SensorData GUI::GetSensorData() const
{
	return m_sensorData;
}

void GUI::SetSensorData(SensorData data)
{
	SetStatus(data.sensorStatus);
	m_sensorData = data;
}

void GUI::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		//NotifyObservers();
	}
}

void GUI::SetUserInput(int _userInput)
{
	m_sensorData.inputOutput = _userInput;
}