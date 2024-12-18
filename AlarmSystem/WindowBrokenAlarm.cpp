#include "WindowBrokenAlarm.h"

WindowBrokenAlarm::WindowBrokenAlarm(ISensor* sensor) : m_sensor(sensor)
{
	//std::shared_ptr<WindowBrokenAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<WindowBrokenAlarm>(this));
}

WindowBrokenAlarm::~WindowBrokenAlarm()
{
	std::shared_ptr<WindowBrokenAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);
}

void WindowBrokenAlarm::Update(SensorStatusEnum status)
{
	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Window Broken! ";

		Logger::GetInstance().Log(message);
		std::cout << "Window Broken! " << std::endl;
	}
}

void WindowBrokenAlarm::SetAlarmStatus(SensorStatusEnum status)
{
	m_alarmstatus = status;
}