#pragma once
#include <iostream>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"
 
class FierAlarm : public IObserver {
public:
	explicit FierAlarm(ISensor* sensor);
	~FierAlarm();
	void Update(SensorStatusEnum status);
	void SetAlarmStatus(SensorStatusEnum status);


private:
	ISensor* m_sensor;
	SensorStatusEnum m_alarmstatus;
};
