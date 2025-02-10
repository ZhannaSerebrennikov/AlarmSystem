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
	bool IsActive() const override;
	void UpdateAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override {
		std::cout << "Windows Broken Alarm triggered! Sensor MacAdress " << m_sensor->GetSensorData().macAddress << std::endl;
	}

private:
	ISensor* m_sensor;
	SensorStatusEnum m_alarmstatus;
};