#pragma once
#include <vector>
#include <memory>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"
#include "Motion.h"
#include "Door.h"

class BulglarAlarm : public IObserver {
public:
	explicit BulglarAlarm(ISensor* sensor);
	~BulglarAlarm();
	void Update(SensorStatusEnum status);
	bool IsActive() const;
	void UpdateAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override;


private:
	void CheckAlarmConditions();
	SensorStatusEnum alarmStatus;
	static std::vector<Motion*> m_motionSensor;
	static std::vector<Door*> m_doorSensor;
	bool m_motionDetected;
	bool m_doorOpenDetected;
	static bool m_isActive;
};