#pragma once
#include <mutex>
#include "../DataHelper/MessageQueue.h"
#include "../DataHelper/MessagePacket.h"
#include "../DataHelper/ObjectType.h"
#include "../AlarmSystem/Logger.h"
#include "../Communication/RFCommunication.h"

class IHDevice {
public:
	virtual void Operate() = 0;
	virtual void ListenToControlPanel() = 0;
	virtual void SendPacket(SensorData& m_sensorData) = 0;

	virtual ~IHDevice() = default;
};