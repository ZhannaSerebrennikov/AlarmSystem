#include "Siren.h"
#include "DoorOpenAlarm.h"
#include "IObserver.h"

Siren::Siren(SensorData sensorData) : m_sensorData(sensorData)
{
	//std::shared_ptr<IObserver> observer = std::make_shared<DoorOpenAlarm>(this);

	//this->AddObserver(observer);
}

SensorData Siren::GetSensorData() const
{
	return m_sensorData;
}


void Siren::SetSensorData(SensorData data)
{
	m_sensorData = data;
}

void Siren::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		NotifyObservers();
	}
}

SensorStatusEnum Siren::GetStatus() const
{
	return m_sensorData.sensorStatus;
}

ObjectTypeEnum Siren::GetSensorType() const
{
	return m_sensorData.objType;
}

void Siren::AddObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.push_back(observer);
}

void Siren::RemoveObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Siren::NotifyObservers()
{
	for (std::shared_ptr<IObserver> observer : m_observers)
	{
		observer->Update(m_sensorData.sensorStatus);
	}
}


const std::vector<std::shared_ptr<IObserver>>& Siren::GetObservers() const {
	return m_observers;
}