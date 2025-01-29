#pragma once
#include <vector>
#include <string>
#include "IDevice.h"
#include "IObserver.h"
#include "AlarmSystemState.h"
#include "../DataHelper/ObjectType.h"
#include <memory>


struct GUIData {
	std::vector<std::shared_ptr<IObserver>> activeAlarms;
	AlarmSystemState* systemState;
};

class GUI : public IDevice {
private:
	std::vector<std::shared_ptr<IObserver>> m_ActiveAlarms;
	AlarmSystemState* m_systemState;
	const std::vector<std::shared_ptr<IObserver>> GetActiveAlarms();
	SensorData m_sensorData;
public:
	GUI(SensorData sensorData);
	SensorData GetSensorData() const override;
	void SetSensorData(SensorData data);
	void SetActiveAlarms(const std::vector<std::shared_ptr<IObserver>>& activeAlarms);
	void RemoveActiveAlarm(std::string alarmToRemove);
	void SetSystemState(AlarmSystemState& _systemState);
	const GUIData GetData();
	void SetStatus(const SensorStatusEnum& newStatus);
	void SetUserInput(int _userInput);
};