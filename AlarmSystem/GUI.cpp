#include "GUI.h"

GUI::GUI() 
{

}

void GUI::SetActiveAlarms(std::string activeAlarm)
{
	m_AcriveAlarms.push_back(activeAlarm);
}

std::vector<std::string> GUI::GetActiveAlarms()
{
	return m_AcriveAlarms;
}

void GUI::RemoveActiveAlarm(std::string alarmToRemove)
{
	//TODO
}