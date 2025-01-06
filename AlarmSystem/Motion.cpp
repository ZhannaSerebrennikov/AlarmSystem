#include "Motion.h"
#include "FierAlarm.h"

Motion::Motion(SensorData sensorData) :m_sensorData(sensorData)
{
	std::shared_ptr<IObserver> observer = std::make_shared<FierAlarm>(this);

	this->AddObserver(observer);
}

SensorData Motion::GetSensorData() const
{
	return m_sensorData;
}

void Motion::SetSensorData(SensorData data)
{
	SetStatus(data.sensorStatus);
	m_sensorData = data;
}

void Motion::SetStatus(const SensorStatusEnum& newStatus)
{
	if (newStatus != m_sensorData.sensorStatus)
	{
		m_sensorData.sensorStatus = newStatus;
		NotifyObservers();
	}
}

SensorStatusEnum Motion::GetStatus() const
{
	return m_sensorData.sensorStatus;
}

ObjectTypeEnum Motion::GetSensorType() const
{
	return m_sensorData.objType;
}

void Motion::AddObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.push_back(observer);
}

void Motion::RemoveObserver(std::shared_ptr<IObserver> observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Motion::NotifyObservers()
{
	for (std::shared_ptr<IObserver> observer : m_observers)
	{
		observer->Update(m_sensorData.sensorStatus);
	}
}