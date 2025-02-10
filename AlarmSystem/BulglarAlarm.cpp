#include <iostream>
#include "BulglarAlarm.h"

std::vector<Motion*> BulglarAlarm::m_motionSensor;
std::vector<Door*> BulglarAlarm::m_doorSensor;
bool BulglarAlarm::m_isActive = false;

BulglarAlarm::BulglarAlarm(ISensor* sensor) : m_motionDetected(false), m_doorOpenDetected(false)
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
}

void BulglarAlarm::Update(SensorStatusEnum status)
{
	CheckAlarmConditions();
	if (m_isActive)
	{
		UpdateAlarmStatus(SensorStatusEnum::ALARM);
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

void BulglarAlarm::UpdateAlarmStatus(SensorStatusEnum status)
{
	alarmStatus = status;
}

bool BulglarAlarm::IsActive() const
{
	return m_isActive;
}

void BulglarAlarm::DisplayAlarm() const
{
	if (m_isActive)
	{
		std::cout << "Bulglary Alarm triggered! MotionDetected and Door Opened Sensor MacAdress " << std::endl;
	}	
}