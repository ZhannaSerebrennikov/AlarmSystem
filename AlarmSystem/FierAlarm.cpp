#include "FierAlarm.h"

FierAlarm::FierAlarm(ISensor* sensor): m_sensor(sensor), m_alarmStatus(new AlarmStatus())
{
	//std::shared_ptr<FierAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<FierAlarm>(this));
}

FierAlarm::~FierAlarm()
{
	std::shared_ptr<FierAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);

	delete m_alarmStatus;
}

void FierAlarm::Update(SensorStatusEnum status)
{
	m_alarmStatus->SetAlarmStatus(status);

	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Fier Alarm! ";

		Logger::GetInstance().Log(message);
		std::cout << "Fier Alarm! " << std::endl;
	}
}


bool FierAlarm::IsActive() const
{
	return m_alarmStatus->IsActive();
}

void FierAlarm::DisplayAlarm() const
{
	std::cout << "Fire Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
}