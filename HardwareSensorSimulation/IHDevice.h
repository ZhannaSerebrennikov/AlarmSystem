#pragma once

class IHDevice {
public:
	virtual void Operate() = 0;
	virtual void ListenToControlPanel() = 0;
	virtual void SendPacket(SensorData& m_sensorData) = 0;

	virtual ~IHDevice() = default;
};