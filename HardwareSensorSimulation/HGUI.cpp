#include <iostream>
#include "HGUI.h"

std::mutex HGUI::m_mtx;

HGUI::HGUI(SensorData& sensordata) : m_sensorData(sensordata)
{
}

void HGUI::Operate()
{
	while (true)
	{
		//m_mtx.lock();
		if (m_IsTriggered)
		{
			SendPacket(m_sensorData);
		}
		ListenToControlPanel();
		//m_mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void HGUI::SendPacket(SensorData& m_sensorData)
{
	/*MessagePacket msg;

	msg.CreatePacket(m_sensorData, 0);
	RFCommunication::SendPacket(msg);

	std::string message = "Sensor " + std::to_string(m_sensorData.macAddress) + " SENT: Data from sensor" + std::to_string(m_sensorData.macAddress) + ".";
	Logger::GetInstance().Log(message);

	std::cout << "Sensor " << m_sensorData.macAddress << " SENT: Data from sensor" << m_sensorData.macAddress << std::endl;*/
}

void HGUI::ListenToControlPanel() 
{
	if (RFCommunication::HasMessage())
	{
		int dstMakadrr = RFCommunication::GetMessageDstMacAdress();
		if (dstMakadrr == m_sensorData.macAddress)
		{
			MessagePacket msg = RFCommunication::ReceivePacket();
			std::string message = "Sensor " + std::to_string(msg.GetDstMacAddress()) + " RECEIVED data from Control Panel" + ".";
			Logger::GetInstance().Log(message);
			
			if (msg.GetSensorData().inputOutput == 3)
			{
				std::vector<std::shared_ptr<IObserver>> tempDeviceData = msg.GetDeviceData();
				for (auto it = tempDeviceData.begin(); it != tempDeviceData.end(); ++it) {
					//std::shared_ptr<IObserver> observer = *it;
					(*it)->DisplayAlarm();  // Assuming IObserver has a method DisplayAlarm
				}
			}
			std::cout << "Sensor " << msg.GetDstMacAddress() << " RECEIVED data from Control Panel" << std::endl;
			std::cout << "A " << msg.GetDstMacAddress() << " RECEIVED data from Control Panel" << std::endl;
			SendPacket(m_sensorData);
		}
	}
}
void HGUI::ShowMenu()
{
	std::cout << "\n 1. Trigger Sensor\n 2. Remove Alarm\n 3. Display All Alarms\n 4. Display Conected Sensors\n 5.  Exit" << std::endl;
}

/*void HDoor::ListenToControlPanel() {

	if (RFCommunication::ReceivePacket().GetDstMacAddress() == m_sensorData.macAddress)
	{
		SensorData temp = RFCommunication::ReceivePacket().GetSensorData();

		if (m_sensorData.sensorStatus == SensorStatusEnum::OK)
			m_sensorData = temp;

		std::cout << "Data of  sensor mackAddress " << m_sensorData.macAddress << "was receved from Contro Panel" << std::endl;
		//m_sensorData.sensorStatus = SensorStatusEnum::OK;
		std::cout << "Data of  sensor mackAddress " << m_sensorData.macAddress << "was send to Control Panel with current status " << ObjectType::SensorStatusEnumToString(m_sensorData.sensorStatus)<< std::endl;

		SendPacket(m_sensorData);
	}
}*/