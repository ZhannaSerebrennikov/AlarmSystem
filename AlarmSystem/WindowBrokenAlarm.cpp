#include "WindowBrokenAlarm.h"

WindowBrokenAlarm::WindowBrokenAlarm(ISensor* sensor) : m_sensor(sensor), m_alarmStatus(new AlarmStatus())
{
	//std::shared_ptr<WindowBrokenAlarm> sharedPtr(this);
	//m_sensor->AddObserver(std::shared_ptr<WindowBrokenAlarm>(this));
}

WindowBrokenAlarm::WindowBrokenAlarm(const  WindowBrokenAlarm& _other)
{
	this->m_sensor = _other.m_sensor;
	this->m_alarmStatus = new AlarmStatus(*_other.m_alarmStatus);
}

WindowBrokenAlarm& WindowBrokenAlarm::operator=(const WindowBrokenAlarm& _other)
{
	if (this != &_other)
	{
		this->m_sensor = _other.m_sensor;

		if (this->m_alarmStatus != nullptr)
			delete this->m_alarmStatus;
		this->m_alarmStatus = new AlarmStatus(*_other.m_alarmStatus);
	}
	return *this;
}

WindowBrokenAlarm::~WindowBrokenAlarm()
{
	std::shared_ptr<WindowBrokenAlarm> sharedPtr(this);
	m_sensor->RemoveObserver(sharedPtr);

	delete m_alarmStatus;
}

void WindowBrokenAlarm::Update(SensorStatusEnum status)
{
	m_alarmStatus->SetAlarmStatus(status);

	if (status == SensorStatusEnum::ALARM)
	{
		std::string message = "Window Broken! ";

		Logger::GetInstance().Log(message);
		std::cout << "Window Broken! " << std::endl;
	}
}

bool WindowBrokenAlarm::IsActive() const
{
	return m_alarmStatus->IsActive();
}

void WindowBrokenAlarm::DisplayAlarm() const
{
	std::cout << "Windows Broken Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
}