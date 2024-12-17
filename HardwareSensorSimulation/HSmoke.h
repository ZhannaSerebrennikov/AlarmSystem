#pragma once
#include "IHSensor.h"

class HSmoke : public IHSensor {
public:
	HSmoke(SensorData& sensordata);

	void Operate();
	void SendPacket(SensorData& m_sensorData);
	void ListenToControlPanel();

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	static std::mutex m_mtx;
};