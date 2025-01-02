#include <iostream>
#include "HMotion.h"

std::mutex HMotion::m_mtx;

HMotion::HMotion(SensorData& sensordata) : m_sensorData(sensordata)
{
}

void HMotion::Operate()
{
	while (true)
	{
		m_mtx.lock();
		if (m_IsTriggered)
		{
			SendPacket(m_sensorData);
		}
		ListenToControlPanel();
		m_mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void HMotion::SendPacket(SensorData& m_sensorData)
{
	MessagePacket msg;

	msg.CreatePacket(m_sensorData, 0);
	RFCommunication::SendPacket(msg);

	std::string message = "Sensor " + std::to_string(m_sensorData.macAddress) + " SENT: Data from sensor" + std::to_string(m_sensorData.macAddress) + ".";
	Logger::GetInstance().Log(message);

	std::cout << "Sensor " << m_sensorData.macAddress << " SENT: Data from sensor" << m_sensorData.macAddress << std::endl;
}

void HMotion::ListenToControlPanel()
{
	if (RFCommunication::HasMessage())
	{
		if (RFCommunication::GetMessageDstMacAdress() == m_sensorData.macAddress)
		{
			MessagePacket msg = RFCommunication::ReceivePacket();
			std::string message = "Sensor " + std::to_string(msg.GetDstMacAddress()) + " RECEIVED data from Control Panel" + ".";
			Logger::GetInstance().Log(message);

			std::cout << "Sensor " << msg.GetDstMacAddress() << " RECEIVED data from Control Panel" << std::endl;

			SendPacket(m_sensorData);
		}
	}
}