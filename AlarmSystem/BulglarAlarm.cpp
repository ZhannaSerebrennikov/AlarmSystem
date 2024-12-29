#include <iostream>
#include "BulglarAlarm.h"

BulglarAlarm::BulglarAlarm(ISensor* sensor) : m_sensor(sensor)
{
	//std::shared_ptr<BulglarAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<BulglarAlarm>(this));
}

BulglarAlarm::~BulglarAlarm()
{
	std::shared_ptr<BulglarAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);
}

void BulglarAlarm::Update(SensorStatusEnum status)
{
	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Bulglary Alarm! ";

		Logger* logger = Logger::GetInstance();
		logger->Log(message);

		std::cout << "Bulglary Alarm! " << std::endl;
	}
}

void BulglarAlarm::SetAlarmStatus(SensorStatusEnum status)
{
	alarmStatus = status;
}