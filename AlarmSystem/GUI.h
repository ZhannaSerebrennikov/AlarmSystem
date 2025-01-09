#pragma once
#include <vector>
#include <string>
#include "IDevice.h"

class GUI : public IDevice {
private:
	std::vector<std::string> m_AcriveAlarms;//List??
public:
	GUI();
	void SetActiveAlarms(std::string activeAlarm);
	std::vector<std::string> GetActiveAlarms();
	void RemoveActiveAlarm(std::string alarmToRemove);
};