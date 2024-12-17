#pragma once
#include <mutex>
#include "../Communication/RFCommunication.h"
#include "../DataHelper/MessageQueue.h"
#include "../DataHelper/ObjectType.h"


class IHSensor {
public:
	virtual ~IHSensor() {}
	virtual void Operate() = 0;
	virtual void ListenToControlPanel() = 0;
	virtual void SendPacket(SensorData& m_sensorData) = 0;
};