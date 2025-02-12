#include "MotionAlarm.h"

MotionAlarm::MotionAlarm(ISensor* sensor) : m_sensor(sensor), m_alarmStatus(new AlarmStatus())
{
	//std::shared_ptr<FierAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<FierAlarm>(this));
}

MotionAlarm::~MotionAlarm()
{
	std::shared_ptr<MotionAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);

	delete m_alarmStatus;
}

void MotionAlarm::Update(SensorStatusEnum status)
{
	m_alarmStatus->SetAlarmStatus(status);

	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Motion Detection Alarm! ";

		Logger::GetInstance().Log(message);
		std::cout << "Motion Alarm! " << std::endl;
	}
}

bool MotionAlarm::IsActive() const
{
	return m_alarmStatus->IsActive();
}

void MotionAlarm::DisplayAlarm() const
{
	std::cout << "Motion Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
}