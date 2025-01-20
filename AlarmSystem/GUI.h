#pragma once
#include <vector>
#include <string>
#include "IDevice.h"
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include <memory>

class GUI : public IDevice {
private:
	std::vector<std::shared_ptr<IObserver>> m_ActiveAlarms;
	const std::vector<std::shared_ptr<IObserver>> GetActiveAlarms();
	SensorData m_sensorData;
public:
	GUI(SensorData sensorData);
	SensorData GetSensorData() const override;
	void SetActiveAlarms(const std::vector<std::shared_ptr<IObserver>>& activeAlarms);
	void RemoveActiveAlarm(std::string alarmToRemove);
	const std::vector<std::shared_ptr<IObserver>> GetData();
};