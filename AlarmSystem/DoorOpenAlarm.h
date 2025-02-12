#pragma once
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"
#include "AlarmStatus.h"

class DoorOpenAlarm : public IObserver {
public:
	explicit DoorOpenAlarm(ISensor* sensor);
	~DoorOpenAlarm();

	void Update(SensorStatusEnum status) override;//OnNotify
	bool IsActive() const override;
	void DisplayAlarm() const override;

private:
	//SensorStatusEnum m_alarmStatus;
	AlarmStatus* m_alarmStatus;
	ISensor* m_sensor;
};