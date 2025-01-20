#pragma once
#include "IHSensor.h"

class HMotion : public IHSensor {
public:
	HMotion(const SensorData& sensordata);

	void Operate() override;
	void SendPacket(SensorData& m_sensorData) override;
	void ListenToControlPanel() override;

	~HMotion() = default;

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	//MessageQueue& m_messageQueue;
	static std::mutex m_mtx;
};
