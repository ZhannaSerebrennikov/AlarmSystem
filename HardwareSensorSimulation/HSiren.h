#pragma once
#include "IHSensor.h"
#include "../DataHelper/MessageQueue.h"

class HSiren :public IHSensor {
public:
	HSiren(const SensorData& sensordata);
	void Operate() override;
	void ListenToControlPanel() override;
	void SendPacket(SensorData& m_sensorData) override;

	~HSiren() = default;
private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	static std::mutex m_mtx;
};
