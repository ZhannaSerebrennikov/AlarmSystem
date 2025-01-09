#pragma once
#include "IHSensor.h"


class HGUI : public IHSensor
{
public:
	HGUI(SensorData& sensordata);

	void Operate();
	void SendPacket(SensorData& m_sensorData);
	void ListenToControlPanel();

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	//MessageQueue& m_messageQueue;
	static std::mutex m_mtx;
};