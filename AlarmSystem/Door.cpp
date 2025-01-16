#include "Door.h"
#include "IObserver.h"
#include "DoorOpenAlarm.h"
#include "BulglarAlarm.h"

Door::Door(SensorData sensorData) : m_sensorData(sensorData)
{
	std::shared_ptr<IObserver> doorOpenAlarm = std::make_shared<DoorOpenAlarm>(this);
	std::shared_ptr<IObserver> bulglarAlarm = std::make_shared<BulglarAlarm>(this);

	this->AddObserver(doorOpenAlarm);
	this->AddObserver(bulglarAlarm);
}

SensorData Door::GetSensorData() const
{
	return m_sensorData;
}

void Door::SetSensorData(SensorData data)
{
	SetStatus(data.sensorStatus);
	m_sensorData = data;
}

void Door::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		NotifyObservers();
	}	
}

SensorStatusEnum Door::GetStatus() const
{
	return m_sensorData.sensorStatus;
}

ObjectTypeEnum Door::GetSensorType() const
{
	return m_sensorData.objType;
}

void Door::AddObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.push_back(observer);
}

void Door::RemoveObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Door::NotifyObservers()
{
	for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
	{
		(*it)->Update(m_sensorData.sensorStatus);
	}
}

const std::vector<std::shared_ptr<IObserver>>& Door::GetObservers() const {
	return m_observers;
}