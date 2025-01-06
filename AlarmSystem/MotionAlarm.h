#pragma once
#include <iostream>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class MotionAlarm : public IObserver {
public:
	explicit MotionAlarm(ISensor* sensor);
	~MotionAlarm();
	void Update(SensorStatusEnum status);
	void SetAlarmStatus(SensorStatusEnum status);


private:
	ISensor* m_sensor;
	SensorStatusEnum m_alarmstatus;
};
