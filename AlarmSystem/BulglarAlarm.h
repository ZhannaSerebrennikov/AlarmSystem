#pragma once
#include <vector>
#include <memory>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"
#include "Motion.h"
#include "Door.h"
#include "AlarmStatus.h"

class BulglarAlarm : public IObserver {
public:
	explicit BulglarAlarm(ISensor* sensor);
	BulglarAlarm(const BulglarAlarm& other);
	BulglarAlarm& operator=(const BulglarAlarm& other);
	~BulglarAlarm();
	void Update(SensorStatusEnum status) override;
	bool IsActive() const override;
	void UpdateAlarmStatus(SensorStatusEnum status);
	void DisplayAlarm() const override;


private:
	void CheckAlarmConditions();
	AlarmStatus* m_alarmStatus;
	static std::vector<Motion*> m_motionSensor;
	static std::vector<Door*> m_doorSensor;
	bool m_motionDetected;
	bool m_doorOpenDetected;
	static bool m_isActive;
};