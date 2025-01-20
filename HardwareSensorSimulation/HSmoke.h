#pragma once
#include "IHSensor.h"

class HSmoke : public IHSensor {
public:
	HSmoke(const SensorData& sensordata);

	void Operate() override;
	void SendPacket(SensorData& m_sensorData) override;
	void ListenToControlPanel() override;

	~HSmoke() = default;
private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	static std::mutex m_mtx;
};