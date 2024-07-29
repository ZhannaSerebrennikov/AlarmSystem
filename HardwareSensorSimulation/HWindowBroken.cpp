#include <iostream>
#include "HWindowBroken.h"

std::mutex HWindowBroken::m_mtx;

HWindowBroken::HWindowBroken(SensorData& sensordata, MessageQueue& mq) : m_sensorData(sensordata), m_messageQueue(mq)
{
}


void HWindowBroken::Operate()
{
	while (true)
	{
		m_mtx.lock();
			ListenToControlPanel();
		m_mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void HWindowBroken::ListenToControlPanel() {
	if (!m_messageQueue.IsEmpty() && m_messageQueue.GetQueueDstMacAddress() == m_sensorData.macAddress) {
		m_sensorData = m_messageQueue.Receive().GetSensorData();;

		std::cout << "Data of  sensor mackAddress " << m_sensorData.macAddress << "was receved" << std::endl;
		m_sensorData.sensorStatus = SensorStatusEnum::OK;
		std::cout << "Data of  sensor mackAddress " << m_sensorData.macAddress << "was send with new status" << std::endl;

		MessagePacket packet;
		packet.CreatePacket(m_sensorData, 0);
		m_messageQueue.Send(packet);
	}
}