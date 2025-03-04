#pragma once
#include "IHDevice.h"


class HGUI : public IHDevice
{
public:
	HGUI(SensorData& sensordata);

	void Operate() override;
	void SendPacket(SensorData& m_sensorData) override;
	void ListenToControlPanel() override;
	void ShowMenu();
	void ShowSystemStateMenu();

private:
	SensorData m_sensorData;
	bool m_IsTriggered = false;
	//MessageQueue& m_messageQueue;
	static std::mutex m_mtx;
};