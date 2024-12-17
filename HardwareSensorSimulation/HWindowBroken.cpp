#include <iostream>
#include "HWindowBroken.h"

std::mutex HWindowBroken::m_mtx;

HWindowBroken::HWindowBroken(SensorData& sensordata) : m_sensorData(sensordata)
{
}


void HWindowBroken::Operate()
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

		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void HWindowBroken::SendPacket(SensorData& m_sensorData)
{
	MessagePacket msg;

	msg.CreatePacket(m_sensorData, 0);
	RFCommunication::SendPacket(msg);

	std::cout << "Sensor " << m_sensorData.macAddress << " SENT: Data from sensor" << m_sensorData.macAddress << std::endl;
}

void HWindowBroken::ListenToControlPanel()
{
	if (RFCommunication::HasMessage())
	{
		if (RFCommunication::GetMessageDstMacAdress() == m_sensorData.macAddress)
		{
			MessagePacket msg = RFCommunication::ReceivePacket();
			std::cout << "Sensor " << msg.GetDstMacAddress() << " RECEIVED data from Control Panel" << std::endl;

			SendPacket(m_sensorData);
		}
	}
}

/*void HWindowBroken::ListenToControlPanel() {
	if (!m_messageQueue.IsEmpty() && m_messageQueue.GetQueueDstMacAddress() == m_sensorData.macAddress) {
		SensorData temp = m_messageQueue.Dequeue().GetSensorData();

		if (m_sensorData.sensorStatus == SensorStatusEnum::OK)
			m_sensorData = temp;

		std::cout << "Data of  sensor mackAddress " << m_sensorData.macAddress << "was receved from Control Panel" << std::endl;
		//m_sensorData.sensorStatus = SensorStatusEnum::OK;
		std::cout << "Data of  sensor mackAddress " << m_sensorData.macAddress << "was send to Control Panel with current status" << std::endl;

		MessagePacket packet;
		packet.CreatePacket(m_sensorData, 0);
		m_messageQueue.Enqueue(packet);
	}
}*/