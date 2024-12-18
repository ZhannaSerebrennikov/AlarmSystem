#include "FierAlarm.h"

FierAlarm::FierAlarm(ISensor* sensor): m_sensor(sensor)
{
	//std::shared_ptr<FierAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<FierAlarm>(this));
}

FierAlarm::~FierAlarm()
{
	std::shared_ptr<FierAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);
}

void FierAlarm::Update(SensorStatusEnum status)
{
	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Fier Alarm! ";

		Logger::GetInstance().Log(message);
		std::cout << "Fier Alarm! " << std::endl;
	}
}

void FierAlarm::SetAlarmStatus(SensorStatusEnum status)
{
	m_alarmstatus = status;
}