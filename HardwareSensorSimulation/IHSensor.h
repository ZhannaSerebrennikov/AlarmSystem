#pragma once
#include <mutex>
#include "../Communication/RFCommunication.h"
#include "../DataHelper/MessageQueue.h"
#include "../DataHelper/ObjectType.h"
#include "../AlarmSystem/Logger.h"
#include "../HardwareSensorSimulation/IHDevice.h"


class IHSensor : public IHDevice{
public:
	virtual ~IHSensor() = default;
	//virtual void Operate() = 0;
	//virtual void ListenToControlPanel() = 0;
	//virtual void SendPacket(SensorData& m_sensorData) = 0;
};