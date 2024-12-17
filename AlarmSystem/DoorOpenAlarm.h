#pragma once
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class DoorOpenAlarm : public IObserver {
public:
	explicit DoorOpenAlarm(ISensor* sensor);
	~DoorOpenAlarm();

	void Update(SensorStatusEnum status);//OnNotify
	void SetAlarmStatus(SensorStatusEnum status);

private:
	SensorStatusEnum alarmStatus;
	ISensor* m_sensor;
};