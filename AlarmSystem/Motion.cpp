#include "Motion.h"
#include "MotionAlarm.h"
#include "BulglarAlarm.h"

Motion::Motion(SensorData sensorData) :m_sensorData(sensorData)
{
	std::shared_ptr<IObserver> observer = std::make_shared<MotionAlarm>(this);
	this->AddObserver(observer);

	std::shared_ptr<IObserver> bulglaryAlarm = std::make_shared<BulglarAlarm>(this);
	this->AddObserver(bulglaryAlarm);
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

const std::vector<std::shared_ptr<IObserver>>& Motion::GetObservers() const {
	return m_observers;
}