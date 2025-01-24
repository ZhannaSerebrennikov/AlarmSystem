#pragma once
#include <string>
#include "IHDevice.h"

class HKeyPad : public IHDevice
{
public:
	HKeyPad(SensorData& sensorData);

	void Operate() override;
	void SendPacket(SensorData& m_sensorData) override;
	void ListenToControlPanel() override;
	void GetUserInput();

private:
	SensorData m_sensorData;
	bool m_IsTriggered;
	std::string m_userInput;

	static std::mutex m_mtx;

	void SetUserInput(std::string _userInpit);
};