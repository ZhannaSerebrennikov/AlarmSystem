#pragma once
#include "IHSensor.h"
#include "../DataHelper/MessageQueue.h"

class HSmoke : public IHSensor {
public:
	HSmoke(SensorData& sensordata, MessageQueue& mq);
	void Operate();
	void ListenToControlPanel();

private:
	SensorData m_sensorData;
	MessageQueue& m_messageQueue;
	static std::mutex m_mtx;
};