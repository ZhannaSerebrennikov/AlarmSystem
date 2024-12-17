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
	if (status == SensorStatusEnum::ALARM)
	{
		std::cout << "Door Open Alarm! " << std::endl;
	}
}

void DoorOpenAlarm::SetAlarmStatus(SensorStatusEnum status)
{
	alarmStatus = status;
}