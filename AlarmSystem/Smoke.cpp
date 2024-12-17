#include "Smoke.h"
#include "FierAlarm.h"

Smoke::Smoke(SensorData sensorData) :m_sensorData(sensorData)
{
	std::shared_ptr<IObserver> observer = std::make_shared<FierAlarm>(this);

	this->AddObserver(observer);
}

SensorData Smoke::GetSensorData() const
{
	return m_sensorData;
}

void Smoke::SetSensorData(SensorData data)
{
	SetStatus(data.sensorStatus);
	m_sensorData = data;
}

void Smoke::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		NotifyObservers();
	}
}

SensorStatusEnum Smoke::GetStatus() const
{
	return m_sensorData.sensorStatus;
}

ObjectTypeEnum Smoke::GetSensorType() const
{
	return m_sensorData.objType;
}

void Smoke::AddObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.push_back(observer);
}

void Smoke::RemoveObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Smoke::NotifyObservers()
{
	for (std::shared_ptr<IObserver> observer : m_observers)
	{
		observer->Update(m_sensorData.sensorStatus);
	}
}