#pragma once
#include "IHSensor.h"
#include "../DataHelper/MessageQueue.h"

class HSiren :public IHSensor {
public:
	HSiren(SensorData& sensordata);
	void Operate();
	void ListenToControlPanel();
	void SendPacket(SensorData& m_sensorData);

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	static std::mutex m_mtx;
};
