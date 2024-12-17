#pragma once
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class BulglarAlarm : public IObserver {
public:
	explicit BulglarAlarm(ISensor* sensor);
	~BulglarAlarm();
	void Update(SensorStatusEnum status);

	void SetAlarmStatus(SensorStatusEnum status);

private:
	SensorStatusEnum alarmStatus;
	ISensor* m_sensor;
};