#pragma once
#include <iostream>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"
#include "AlarmStatus.h"
 
class FierAlarm : public IObserver {
public:
	explicit FierAlarm(ISensor* sensor);
	~FierAlarm();
	void Update(SensorStatusEnum status) override;
	bool IsActive() const override;
	void DisplayAlarm() const override;

private:
	ISensor* m_sensor;
	AlarmStatus* m_alarmStatus;
};
