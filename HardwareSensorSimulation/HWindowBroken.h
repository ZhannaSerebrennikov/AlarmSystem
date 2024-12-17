#pragma once
#include "IHSensor.h"

class HWindowBroken :public IHSensor {
public:
	HWindowBroken(SensorData& sensordata);

	void Operate();
	void SendPacket(SensorData& m_sensorData);
	void ListenToControlPanel();

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	static std::mutex m_mtx;
};