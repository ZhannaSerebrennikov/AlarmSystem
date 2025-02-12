#include "AlarmStatus.h"

AlarmStatus::AlarmStatus() : m_alarmStatus(SensorStatusEnum::OK), m_isActive(false) {}

bool AlarmStatus::IsActive()
{
	return m_isActive;
}

void AlarmStatus::SetAlarmStatus(SensorStatusEnum _status)
{
	m_alarmStatus = _status;
	m_isActive = (m_alarmStatus == SensorStatusEnum::ALARM) ? true : false;
}

SensorStatusEnum AlarmStatus::GetAlarmStatus() const
{
	return m_alarmStatus;
}