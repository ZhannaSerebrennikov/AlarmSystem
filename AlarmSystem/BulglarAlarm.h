#pragma once
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class BulglarAlarm : public IObserver {
public:
	explicit BulglarAlarm(ISensor* sensor);
	~BulglarAlarm();
	void Update(SensorStatusEnum status);
	bool IsActive() const;
	void SetAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override {
		std::cout << "Bulglary Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
	}

private:
	SensorStatusEnum alarmStatus;
	ISensor* m_sensor;
};