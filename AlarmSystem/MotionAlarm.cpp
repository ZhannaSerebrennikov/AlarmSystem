#include "MotionAlarm.h"

MotionAlarm::MotionAlarm(ISensor* sensor) : m_sensor(sensor)
{
	//std::shared_ptr<FierAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<FierAlarm>(this));
}

MotionAlarm::~MotionAlarm()
{
	std::shared_ptr<MotionAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);
}

void MotionAlarm::Update(SensorStatusEnum status)
{
	UpdateAlarmStatus(status);

	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Motion Detection Alarm! ";

		Logger::GetInstance().Log(message);
		std::cout << "Motion Alarm! " << std::endl;
	}
}

void MotionAlarm::UpdateAlarmStatus(SensorStatusEnum status)
{
	m_alarmstatus = status;
}

bool MotionAlarm::IsActive() const
{
	return m_alarmstatus == SensorStatusEnum::ALARM;
}