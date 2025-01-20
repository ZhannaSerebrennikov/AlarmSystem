#pragma once
#include "IHSensor.h"

class HWindowBroken :public IHSensor {
public:
	HWindowBroken(const SensorData& sensordata);

	void Operate() override;
	void SendPacket(SensorData& m_sensorData) override;
	void ListenToControlPanel() override;

	~HWindowBroken() = default;

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	static std::mutex m_mtx;
};