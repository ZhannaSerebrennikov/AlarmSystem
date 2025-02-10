#include <iostream>
#include "DoorOpenAlarm.h"

DoorOpenAlarm::DoorOpenAlarm(ISensor* sensor): m_sensor(sensor)
{
	//std::shared_ptr<DoorOpenAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<DoorOpenAlarm>(this));
}

DoorOpenAlarm::~DoorOpenAlarm()
{
	std::shared_ptr<DoorOpenAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);
}

void DoorOpenAlarm::Update(SensorStatusEnum status)//OnNotify
{
	UpdateAlarmStatus(status);

	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Door Open Alarm!";

		Logger::GetInstance().Log(message);
		std::cout << "Door Open Alarm! " << std::endl;

	}
}

void DoorOpenAlarm::UpdateAlarmStatus(SensorStatusEnum status)
{
	alarmStatus = status;
}

bool DoorOpenAlarm::IsActive()const
{
	return alarmStatus == SensorStatusEnum::ALARM;
}
