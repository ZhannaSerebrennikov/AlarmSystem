#include <iostream>
#include "ControlPanel.h"
#include "SensorFactory.h"
#include "../DataHelper/TXTDataReader.h"
#include "../DataHelper/MessagePacket.h"
#include "../DataHelper/ObjectType.h"
#include "../Communication/RFCommunication.h"

ControlPanel::ControlPanel(): m_controlPanelMacAddress(0)
{

	std::vector<SensorData> sensorDataFromFile;

	TXTDataReader fileConn("VirtualConnectedSensors.txt");

	fileConn.ParseData(sensorDataFromFile);
	
	AddAllSensorsToControlPanel(sensorDataFromFile);
}

void ControlPanel::AddAllSensorsToControlPanel(std::vector<SensorData>& sensorDataFromFile)
{
	for (const SensorData& data : sensorDataFromFile)
	{
		AddSensorToControlPanel(data);
	}
}

void ControlPanel::AddSensorToControlPanel(SensorData sensordata)
{
	std::shared_ptr<ISensor> temSensor = SensorFactory::CreateObject(sensordata);
	m_sensorVector.push_back(temSensor);
}

void ControlPanel::AlarmToSensorConection()
{
	for (auto it = m_sensorVector.begin(); it != m_sensorVector.end(); ++it)
	{
		if ((*it)->GetSensorType() == ObjectTypeEnum::DOOR)
		{
			
		}

	}
}

void ControlPanel::Start()
{
	while (true)
	{
		Monitoring();
	}
}

void ControlPanel::Monitoring()
{

	int counter = 0;
	MessagePacket packet;

	//for (const auto& sensor : m_sensorVector)
	for(auto it = m_sensorVector.begin(); it != m_sensorVector.end(); ++it)
	{
		counter = counter + 1;
		//while (packet.GetWasSendTimesCounter() < 3 && communication was faild)
		//{
			SendMessage(packet, /*sensor*/(*it));

			if (RFCommunication::GetMessageDstMacAdress() == 0)
			{
				//(*it)->SetSensorData(m_messageQueue.Dequeue().GetSensorData());
				(*it)->SetSensorData(RFCommunication::ReceivePacket().GetSensorData());

				Logger::GetInstance().Log("Data from sensor was received");

				std::cout << "Data from  sensor mackAddress " << (*it)->GetSensorData().macAddress << "was receved with a status "<< ObjectType::SensorStatusEnumToString((*it)->GetSensorData().sensorStatus) <<"." << std::endl;
			}

			std::this_thread::sleep_for(std::chrono::seconds(3));
		//}
		/*if (packet.GetWasSendTimesCounter() == 3)
		{
			std::cout << "Sensor mackAddress " << (*it)->GetSensorData().macAddress << " not answering" << std::endl;
			packet.ResetWasSendTimesCounter();
		}*/
	}
}

void ControlPanel::SendMessage(MessagePacket& packet, std::shared_ptr<ISensor> sensor)
{
	packet.IncreaseWasSendTimesCounter();

	packet.CreatePacket(sensor->GetSensorData(), sensor->GetSensorData().macAddress);

	RFCommunication::SendPacket(packet);
	//m_messageQueue.Enqueue(packet);

	std::cout << "Control Panel Send Message to sensor "<< sensor->GetSensorData().macAddress << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void ControlPanel::ReceiveMessage()
{

}