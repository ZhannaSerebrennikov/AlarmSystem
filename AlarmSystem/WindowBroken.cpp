#include "BulglarAlarm.h"
#include "WindowBrokenAlarm.h"
#include "WindowBroken.h"


WindowBroken::WindowBroken(SensorData sensorData) : m_sensorData(sensorData)
{
	std::shared_ptr<IObserver> windowsBrokenAlarm = std::make_shared<WindowBrokenAlarm>(this);
	this->AddObserver(windowsBrokenAlarm);
}

SensorData WindowBroken::GetSensorData() const
{
	return m_sensorData;
}


void WindowBroken::SetSensorData(SensorData data)
{
	SetStatus(data.sensorStatus);
	m_sensorData = data;
}

void WindowBroken::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		NotifyObservers();
	}
}

SensorStatusEnum WindowBroken::GetStatus() const
{
	return m_sensorData.sensorStatus;
}

ObjectTypeEnum WindowBroken::GetSensorType() const
{
	return m_sensorData.objType;
}

void WindowBroken::AddObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.push_back(observer);
}

void WindowBroken::RemoveObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void WindowBroken::NotifyObservers()
{
	for ( auto it = m_observers.begin(); it!=m_observers.end(); ++it)
	{
		(*it)->Update(m_sensorData.sensorStatus);
	}
}

const std::vector<std::shared_ptr<IObserver>>& WindowBroken::GetObservers() const{
	return m_observers;
}