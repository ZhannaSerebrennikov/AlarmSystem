#include <iostream>
#include "DoorOpenAlarm.h"

DoorOpenAlarm::DoorOpenAlarm(ISensor* sensor): m_sensor(sensor), m_alarmStatus(new AlarmStatus())
{
}

DoorOpenAlarm::DoorOpenAlarm(const DoorOpenAlarm& _other) : m_alarmStatus(new AlarmStatus(*_other.m_alarmStatus))
{
	m_sensor = _other.m_sensor;
}

DoorOpenAlarm& DoorOpenAlarm::operator=(const DoorOpenAlarm& _other)
{
	if (this != &_other)
	{
		if (m_alarmStatus)
			delete m_alarmStatus;
		m_alarmStatus = new AlarmStatus(*_other.m_alarmStatus);
		m_sensor = _other.m_sensor;
	}
	return *this;
}

DoorOpenAlarm::~DoorOpenAlarm()
{
	std::shared_ptr<DoorOpenAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);

	delete m_alarmStatus;
}

void DoorOpenAlarm::Update(SensorStatusEnum status)//OnNotify
{
	m_alarmStatus->SetAlarmStatus(status);
	//The Update method currently only triggers a state change. However, you could consider delegating complex state-handling or state-transitions into a different class. This can prevent the DoorOpenAlarm class from getting overloaded with logic that might change for different alarms.
	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Door Open Alarm!";

		Logger::GetInstance().Log(message);
		std::cout << "Door Open Alarm! " << std::endl;

	}
}

bool DoorOpenAlarm::IsActive()const
{
	return m_alarmStatus->IsActive();
}

void DoorOpenAlarm::DisplayAlarm() const
{
	std::cout << "Door Open Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
}
