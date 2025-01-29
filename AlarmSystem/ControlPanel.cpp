#include <iostream>
#include <string>
#include <memory>
#include "ControlPanel.h"
#include "SensorFactory.h"
#include "../DataHelper/TXTDataReader.h"
#include "../DataHelper/MessagePacket.h"
#include "../DataHelper/ObjectType.h"
#include "../Communication/RFCommunication.h"

ControlPanel::ControlPanel(): m_controlPanelMacAddress(0), m_currentSystemState(std::make_unique<DisarmState>())
{

	std::vector<SensorData> sensorDataFromFile;

	TXTDataReader fileConn("VirtualConnectedSensors.txt");

	fileConn.ParseData(sensorDataFromFile);
	
	RegisterAllComponentsToControlPanel(sensorDataFromFile);

	for (auto it = m_deviceCollection.begin(); it != m_deviceCollection.end(); ++it)
	{
		std::shared_ptr<GUI> guiPtr = std::dynamic_pointer_cast<GUI>(*it);
		if (guiPtr)
		{
			m_gui = guiPtr;
		}
	}
	//RegisterAllDevicesToControlPanel(sensorDataFromFile);
	//m_deviceCollection.push_back(std::make_shared<GUI>());

	//m_gui = std::make_shared<GUI>();
}

ControlPanel::ControlPanel(const ControlPanel& controlPanel) : m_controlPanelMacAddress(controlPanel.m_controlPanelMacAddress)//, stop(controlPanel.stop.load())
{
	for (const auto& sensor : controlPanel.m_sensorCollection)
	{
		//m_sensorCollection.push_back(std::make_shared<ISensor>(&sensor));//deep copy for the m_sensorVector for creating new shared pointers for each object
	}
}

ControlPanel& ControlPanel::operator=(const ControlPanel controlPanel)
{
	if (this == &controlPanel)
	{
		return *this;
	}

	m_controlPanelMacAddress = controlPanel.m_controlPanelMacAddress;
	//stop.store(controlPanel.stop.load());

	for (const auto& sensor : m_sensorCollection) //deep copy
	{
		//m_sensorCollection.push_back(std::make_shared<ISensor>(*sensor));
	}

	return *this;
}

void ControlPanel::RegisterAllComponentsToControlPanel(std::vector<SensorData>& sensorDataFromFile)
{
	for (const SensorData& data : sensorDataFromFile)
	{
		RegisterSensorToControlPanel(data);
		RegisterDeviceToControlPanel(data);
	}
}

void ControlPanel::RegisterSensorToControlPanel(SensorData sensordata)
{
	std::shared_ptr<ISensor> tempSensor = SensorFactory::CreateSensorObject(sensordata);

	if(tempSensor != nullptr)
		m_sensorCollection.push_back(tempSensor);
}

void ControlPanel::RegisterDeviceToControlPanel(SensorData sensordata)
{
	std::shared_ptr<IDevice> tempDevice = SensorFactory::CreateDeviceObject(sensordata);

	if (tempDevice != nullptr)
		m_deviceCollection.push_back(tempDevice);
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
	MessagePacket packet;

	for(auto it = m_sensorCollection.begin(); it != m_sensorCollection.end(); ++it)
	{
		SendMessage(packet, (*it));

		if (RFCommunication::HasMessage() && RFCommunication::GetMessageDstMacAdress() == 0 && (*it)->GetSensorData().macAddress == RFCommunication::GetMessageSrsMacAdress())
		{
			ReceiveMessage((*it));
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	UpdateGUI();

	for (auto it = m_deviceCollection.begin(); it != m_deviceCollection.end(); ++it)
	{
		if (std::dynamic_pointer_cast<GUI>(*it))
		{
			SendMessage(packet, (*it));
		}
		else if (std::dynamic_pointer_cast<KeyPad>(*it))
		{
			if (RFCommunication::HasMessage() && RFCommunication::GetMessageDstMacAdress() == 0 && (*it)->GetSensorData().macAddress == RFCommunication::GetMessageSrsMacAdress())
			{
				ReceiveMessage((*it));
				m_gui->SetUserInput((*it)->GetSensorData().inputOutput);
			}
		}

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void ControlPanel::SendMessage(MessagePacket& packet, std::shared_ptr<IDevice> device)
{
	packet.IncreaseWasSendTimesCounter();
	if (auto sensor = std::dynamic_pointer_cast<ISensor>(device))
	{
		packet.CreatePacket(sensor->GetSensorData(), sensor->GetSensorData().macAddress);

		RFCommunication::SendPacket(packet);
		//m_messageQueue.Enqueue(packet);

		std::string message = "Control Panel Send Message to sensor " + std::to_string(sensor->GetSensorData().macAddress) + ".";

		Logger::GetInstance().Log(message);

		//std::cout << "Control Panel Send Message to sensor " << sensor->GetSensorData().macAddress << std::endl;
	}
	else
	{
		if (std::shared_ptr<GUI> guiDevice = std::dynamic_pointer_cast<GUI>(device))
		{
			packet.CreatePacket(guiDevice->GetData(), guiDevice->GetSensorData(), guiDevice->GetSensorData().macAddress);
		}
		else{
			packet.CreatePacket(device->GetSensorData(), device->GetSensorData().macAddress); // Just an example, you should define packet structure for devices
		}
		
		RFCommunication::SendPacket(packet);

		std::string message = "Control Panel Send Message to device " + std::to_string(device->GetSensorData().macAddress) + ".";
		Logger::GetInstance().Log(message);
	 }
	//std::this_thread::sleep_for(std::chrono::seconds(5));
}

void ControlPanel::ReceiveMessage(std::shared_ptr<IDevice> sensor)
{
	sensor->SetSensorData(RFCommunication::ReceivePacket().GetSensorData());

	std::string message = "Data from  sensor mackAddress " + std::to_string(sensor->GetSensorData().macAddress) + " was receved with a status " + ObjectType::SensorStatusEnumToString(sensor->GetSensorData().sensorStatus) + ".";

	Logger::GetInstance().Log(message);
}

void ControlPanel::UpdateGUI()
{
	CheckForActiveAlarms();
	UpdateGUIWithActiveAlarms();
	UpdateGUIWithSystemState();
}

void ControlPanel::UpdateGUIWithActiveAlarms()
{
	if(m_gui)
	{
		m_gui->SetActiveAlarms(m_activeAlarmCollection);
	}
}

void ControlPanel::UpdateGUIWithSystemState()
{
	if (m_gui)
	{
		m_gui->SetSystemState(*m_currentSystemState);
	}
}




void ControlPanel::ResetActiveAlarmCollection()
{
	m_activeAlarmCollection.clear();
}

void ControlPanel::AddActiveAlarm(std::shared_ptr<IObserver> alarm)
{
	m_activeAlarmCollection.push_back(std::move(alarm));
}

void ControlPanel::RemoveActiveAlarm(std::shared_ptr<IObserver> alarm)
{
	auto it = std::remove(m_activeAlarmCollection.begin(), m_activeAlarmCollection.end(), alarm);
	if (it != m_activeAlarmCollection.end())
	{
		m_activeAlarmCollection.erase(it, m_activeAlarmCollection.end());
	}
}

void ControlPanel::CheckForActiveAlarms()
{
	ResetActiveAlarmCollection();

	for (const auto& sensor : m_sensorCollection)
	{
		const auto& observers = sensor->GetObservers();
		for (const auto& observer : observers)
		{
			if (observer->IsActive())
			{
				AddActiveAlarm(observer);
			}
			else
			{
				RemoveActiveAlarm(observer);
			}
		}
	}
}

void ControlPanel::SetState(std::unique_ptr<AlarmSystemState> _newstate)
{
	m_currentSystemState = std::move(_newstate);
}

void ControlPanel::HandleState() const
{
	m_currentSystemState->Handle();
}