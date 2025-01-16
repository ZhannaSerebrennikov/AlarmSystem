#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ISensor.h"
#include "../DataHelper/ObjectType.h"
#include "../DataHelper/MessageQueue.h"
#include "Logger.h"
#include "GUI.h"


class ControlPanel {
public:
	ControlPanel();
	~ControlPanel() = default;
	ControlPanel(const ControlPanel& controlPanel) = default;
	//ControlPanel& operator=(const ControlPanel controlPanel) = default;

	void RegisterAllComponentsToControlPanel(std::vector<SensorData>& sensorData);
	//void SendActiveAlarmsToGUI();
	void Start();
	void SendMessage(MessagePacket& packet, std::shared_ptr<IDevice> device);
	void ReceiveMessage();

private:
	int m_controlPanelMacAddress;
	std::vector<std::shared_ptr<ISensor>> m_sensorCollection;
	std::vector<std::shared_ptr<IDevice>> m_deviceCollection;
	std::vector<std::shared_ptr<IObserver>> m_activeAlarmCollection;
	//MessageQueue& m_messageQueue;
	std::atomic<bool> stop;
	std::shared_ptr<GUI> m_gui;

	void RegisterSensorToControlPanel(SensorData sensordata);
	void RegisterDeviceToControlPanel(SensorData sensordata);
	void Monitoring();
	void AddActiveAlarm(std::shared_ptr<IObserver> alarm);
	void RemoveActiveAlarm(std::shared_ptr<IObserver> alarm);
	void CheckForActiveAlarms();
	void UpdateGUIWithActiveAlarms();
	void ResetActiveAlarmCollection();
};