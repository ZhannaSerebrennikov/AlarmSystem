#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ISensor.h"
#include "../DataHelper/ObjectType.h"
#include "../DataHelper/MessageQueue.h"
#include "Logger.h"


class ControlPanel {
public:
	ControlPanel();
	~ControlPanel() = default;
	ControlPanel(const ControlPanel& controlPanel) = default;
	//ControlPanel& operator=(const ControlPanel controlPanel) = default;

	void AddAllSensorsToControlPanel(std::vector<SensorData>& sensorData);
	void Start();
	void SendMessage(MessagePacket& packet, std::shared_ptr<ISensor> sensor);
	void ReceiveMessage();
	void AlarmToSensorConection();

private:
	int m_controlPanelMacAddress;
	std::vector<std::shared_ptr<ISensor>> m_sensorVector;
	//MessageQueue& m_messageQueue;
	std::atomic<bool> stop;

	void AddSensorToControlPanel(SensorData sensordata);
	void Monitoring();
};