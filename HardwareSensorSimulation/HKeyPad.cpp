#include "HKeyPad.h"

std::mutex HKeyPad::m_mtx;

HKeyPad::HKeyPad(SensorData& sensorData) : m_sensorData(sensorData), m_IsTriggered(false)
{

}

void HKeyPad::Operate()
{
	while (true)
	{
		//m_mtx.lock();
		if (m_IsTriggered)
		{
			SendPacket(m_sensorData);
			m_IsTriggered = false;
		}
		ListenToControlPanel();
		//m_mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void HKeyPad::SendPacket(SensorData& m_sensorData)
{
	MessagePacket msg;

	msg.CreatePacket(m_sensorData, 0);
	RFCommunication::SendPacket(msg);

	std::string message = "Sensor " + std::to_string(m_sensorData.macAddress) + " SENT: Data from sensor" + std::to_string(m_sensorData.macAddress) + ".";
	Logger::GetInstance().Log(message);
}

void HKeyPad::ListenToControlPanel()//Listen to UserInput
{
	/*while (!m_IsTriggered)
	{
		std::cout << "Keypad is now active. Please enter a code: ";

		std::string m_userInput;
		std::getline(std::cin, m_userInput);
		m_IsTriggered = true;
	}*/

	/*if (RFCommunication::HasMessage())
	{
		if (RFCommunication::GetMessageDstMacAdress() == m_sensorData.macAddress)
		{
			MessagePacket msg = RFCommunication::ReceivePacket();
			std::string message = "Sensor " + std::to_string(msg.GetDstMacAddress()) + " RECEIVED data from Control Panel" + ".";
			Logger::GetInstance().Log(message);

			std::vector<std::shared_ptr<IObserver>> tempDeviceData = msg.GetDeviceData();
			for (auto it = tempDeviceData.begin(); it != tempDeviceData.end(); ++it) {
				//std::shared_ptr<IObserver> observer = *it;
				(*it)->DisplayAlarm();  // Assuming IObserver has a method DisplayAlarm
			}

			std::cout << "Sensor " << msg.GetDstMacAddress() << " RECEIVED data from Control Panel" << std::endl;
			std::cout << "A " << msg.GetDstMacAddress() << " RECEIVED data from Control Panel" << std::endl;
			SendPacket(m_sensorData);
		}
	}*/
}

void HKeyPad::GetUserInput()
{
	std::cout << "Keypad is now active. Please enter a code: ";

	std::getline(std::cin, m_userInput);
	SetUserInput(m_userInput);
	m_IsTriggered = true;
}

void HKeyPad::SetUserInput(std::string _userInpit)
{
	m_sensorData.inputOutput = std::stoi(m_userInput);
}