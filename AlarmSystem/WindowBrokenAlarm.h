#pragma once
#include <iostream>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"
#include "AlarmStatus.h"

class WindowBrokenAlarm : public IObserver {
public:
	explicit WindowBrokenAlarm(ISensor* sensor);
	~WindowBrokenAlarm();
	void Update(SensorStatusEnum status) override;
	bool IsActive() const override;
	void DisplayAlarm() const override;

private:
	ISensor* m_sensor;
	AlarmStatus* m_alarmStatus;
};