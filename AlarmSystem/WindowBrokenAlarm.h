#pragma once
#include <iostream>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class WindowBrokenAlarm : public IObserver {
public:
	explicit WindowBrokenAlarm(ISensor* sensor);
	~WindowBrokenAlarm();
	void Update(SensorStatusEnum status);
	void SetAlarmStatus(SensorStatusEnum status);


private:
	ISensor* m_sensor;
	SensorStatusEnum m_alarmstatus;
};