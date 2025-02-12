#include <iostream>
#include "DoorOpenAlarm.h"

DoorOpenAlarm::DoorOpenAlarm(ISensor* sensor): m_sensor(sensor), m_alarmStatus(new AlarmStatus())
{
	//std::shared_ptr<DoorOpenAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<DoorOpenAlarm>(this));
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
