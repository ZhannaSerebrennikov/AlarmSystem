#pragma once
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class DoorOpenAlarm : public IObserver {
public:
	explicit DoorOpenAlarm(ISensor* sensor);
	~DoorOpenAlarm();

	void Update(SensorStatusEnum status);//OnNotify
	bool IsActive() const override;
	void SetAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override {
		std::cout << "Door Open Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
	}

private:
	SensorStatusEnum alarmStatus;
	ISensor* m_sensor;
};