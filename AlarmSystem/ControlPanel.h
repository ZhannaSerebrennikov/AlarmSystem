#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ISensor.h"
#include "../DataHelper/ObjectType.h"
#include "../DataHelper/MessageQueue.h"
#include "Logger.h"
#include "GUI.h"
#include "KeyPad.h"
#include "AlarmSystemState.h"
#include "DisarmState.h"
#include "ArmState.h"


class ControlPanel {
public:
	ControlPanel();
	~ControlPanel() = default;
	ControlPanel(const ControlPanel& controlPanel);
	ControlPanel& operator=(const ControlPanel controlPanel);

	void RegisterAllComponentsToControlPanel(std::vector<SensorData>& sensorData);
	//void SendActiveAlarmsToGUI();
	void Start();
	void SendMessage(MessagePacket& packet, std::shared_ptr<IDevice> device);
	void ReceiveMessage(std::shared_ptr<IDevice> sensor);
	void SetState(std::unique_ptr<AlarmSystemState> _newstate);
	void HandleState() const;
	void UpdateGUI();

private:
	int m_controlPanelMacAddress;
	std::vector<std::shared_ptr<ISensor>> m_sensorCollection;
	std::vector<std::shared_ptr<IDevice>> m_deviceCollection;
	std::vector<std::shared_ptr<IObserver>> m_activeAlarmCollection;
	std::atomic<bool> stop;
	std::shared_ptr<GUI> m_gui;
	std::shared_ptr<KeyPad> m_keyPad;
	std::unique_ptr<AlarmSystemState> m_currentSystemState;

	void RegisterSensorToControlPanel(SensorData sensordata);
	void RegisterDeviceToControlPanel(SensorData sensordata);
	void Monitoring();
	void AddActiveAlarm(std::shared_ptr<IObserver> alarm);
	void RemoveActiveAlarm(std::shared_ptr<IObserver> alarm);
	void CheckForActiveAlarms();
	void UpdateGUIWithActiveAlarms();
	void ResetActiveAlarmCollection();
	void UpdateGUIWithSystemState();
	void ChangeSystemState();
};