#pragma once
#include "IHSensor.h"

class HDoor: public IHSensor {
public:
	HDoor(const SensorData& sensordata);

	void Operate() override;
	void SendPacket(SensorData& m_sensorData) override;
	void ListenToControlPanel() override;

	~HDoor() = default;

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	//MessageQueue& m_messageQueue;
	static std::mutex m_mtx;
	
};
