#include "GUI.h"

GUI::GUI(SensorData sensorData) : m_sensorData(sensorData)
{

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