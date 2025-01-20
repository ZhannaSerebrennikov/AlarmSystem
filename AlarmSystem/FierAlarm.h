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
	bool IsActive() const override;
	void SetAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override {
		std::cout << "Fire Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
	}

private:
	ISensor* m_sensor;
	SensorStatusEnum m_alarmstatus;
};
