#pragma once
#include "../DataHelper/ObjectType.h"

class AlarmStatus {
public:
	AlarmStatus();
	bool IsActive();
	void SetAlarmStatus(SensorStatusEnum _status);
	SensorStatusEnum GetAlarmStatus() const;

private:
	SensorStatusEnum m_alarmStatus;
	bool m_isActive;
};