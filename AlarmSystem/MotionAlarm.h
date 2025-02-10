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
	bool IsActive() const override;
	void UpdateAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override {
		std::cout << "Motion Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
	}

private:
	ISensor* m_sensor;
	SensorStatusEnum m_alarmstatus;
};
