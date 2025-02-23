#include <iostream>
#include "BulglarAlarm.h"

std::vector<Motion*> BulglarAlarm::m_motionSensor;
std::vector<Door*> BulglarAlarm::m_doorSensor;
bool BulglarAlarm::m_isActive = false;

BulglarAlarm::BulglarAlarm(ISensor* sensor) : m_motionDetected(false), m_doorOpenDetected(false), m_alarmStatus(new AlarmStatus())
{
	if (auto doorSensor = dynamic_cast<Door*>(sensor))
	{
		m_doorSensor.push_back(doorSensor);
	}
	else if(auto motionSensor = dynamic_cast<Motion*>(sensor))
	{
		m_motionSensor.push_back(motionSensor);
	}

}

BulglarAlarm::~BulglarAlarm()
{
	std::shared_ptr<BulglarAlarm> sharedPtr(this);
	for (auto& door : m_doorSensor) {
		door->RemoveObserver(sharedPtr);
	}

	for (auto& motion : m_motionSensor) {
		motion->RemoveObserver(sharedPtr);
	}

	delete m_alarmStatus;
}

BulglarAlarm::BulglarAlarm(const BulglarAlarm& other) : m_alarmStatus(other.m_alarmStatus),m_motionDetected(other.m_motionDetected), m_doorOpenDetected(other.m_doorOpenDetected)
{
	m_motionSensor = other.m_motionSensor;
	m_doorSensor = other.m_doorSensor;
	m_isActive = other.m_isActive;
}

BulglarAlarm& BulglarAlarm::operator=(const BulglarAlarm& other)
{
	if (this != &other)
	{
		if (m_alarmStatus)
			delete m_alarmStatus;

		m_alarmStatus = (other.m_alarmStatus ? new AlarmStatus(*other.m_alarmStatus) : nullptr);
		m_motionDetected = other.m_motionDetected;
		m_doorOpenDetected = other.m_doorOpenDetected;
		m_motionSensor = other.m_motionSensor; // Handle the static member
		m_doorSensor = other.m_doorSensor;     // Handle the static member
		m_isActive = other.m_isActive;
	}
	return *this;
}

void BulglarAlarm::Update(SensorStatusEnum status)
{
	CheckAlarmConditions();
	if (m_isActive)
	{
		m_alarmStatus->SetAlarmStatus(status);
	}
	/// <summary>
	/*if (m_motionSensor->GetStatus() == SensorStatusEnum::ALARM && m_doorSensor->GetStatus() == SensorStatusEnum::ALARM)
	{
		m_isActive = true;
		std::string message = "Bulglary Alarm! ";
		Logger::GetInstance().Log(message);
	}
	else
		m_isActive = false;*/
	/// </summary>
	/// <param name="status"></param>

}

void BulglarAlarm::CheckAlarmConditions()
{
	m_motionDetected = false;
	for (auto& motionSensor : m_motionSensor)
	{
		if (motionSensor->GetStatus() == SensorStatusEnum::ALARM)
		{
			m_motionDetected = true;
			break;
		}
	}
	
	m_doorOpenDetected = false;
	for (auto& doorSensor : m_doorSensor)
	{
		if (doorSensor->GetStatus() == SensorStatusEnum::ALARM)
		{
			m_doorOpenDetected = true;
			break;
		}
	}

	m_isActive = m_motionDetected && m_doorOpenDetected;
}


bool BulglarAlarm::IsActive() const
{
	return m_alarmStatus->IsActive();
}

void BulglarAlarm::DisplayAlarm() const
{
	if (m_isActive)
	{
		std::cout << "Bulglary Alarm triggered! MotionDetected and Door Opened Sensor MacAdress " << std::endl;
	}	
}