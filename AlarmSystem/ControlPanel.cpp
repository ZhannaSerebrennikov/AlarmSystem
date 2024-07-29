#include <iostream>
#include "ControlPanel.h"
#include "SensorFactory.h"
#include "../DataHelper/TXTDataReader.h"
#include "../DataHelper/MessagePacket.h"

ControlPanel::ControlPanel(MessageQueue& messageQueue): m_controlPanelMacAddress(0), m_messageQueue(messageQueue)
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

	for (auto sensor : m_sensorVector)
	{
		while (packet.GetWasSendTimesCounter() < 3)
		{
			SendMessage(packet, sensor);

			if (!m_messageQueue.IsEmpty() && m_messageQueue.GetQueueDstMacAddress() == 0)
			{
				sensor->SetSensorData(m_messageQueue.Receive().GetSensorData());

				std::cout << "Data of  sensor mackAddress " << sensor->GetSensorData().macAddress << "was receved with a new status OK" << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		if(packet.GetWasSendTimesCounter() == 3)
		{
			std::cout << "Sensor mackAddress " << sensor->GetSensorData().macAddress << " not answering" << std::endl;
			packet.ResetWasSendTimesCounter();
		}
	}
}

void ControlPanel::SendMessage(MessagePacket& packet, std::shared_ptr<ISensor> sensor)
{
	packet.IncreaseWasSendTimesCounter();

	packet.CreatePacket(sensor->GetSensorData(), sensor->GetSensorData().macAddress);
	m_messageQueue.Send(packet);

	std::cout << "Control Panel Send Message" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void ControlPanel::ReceiveMessage()
{

}