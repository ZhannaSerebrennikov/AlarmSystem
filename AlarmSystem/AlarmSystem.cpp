#include "AlarmSystem.h"
#include <memory>

AlarmSystem::AlarmSystem()
{
	Logger::GetInstance().OpenLogFile("LogFile.txt");
	CreateHardwareDevices(v_hardwareSensorsDevices, v_threads);
	checForGUIdevice();
	checkForKeyPadDevice();
}

AlarmSystem::~AlarmSystem()
{
	Logger::GetInstance().CloseLogFile();
}

void AlarmSystem::Run()
{
	for (auto& thread : v_threads) {

		thread.detach();
	}

	std::thread cpThread(&ControlPanel::Start, &mainPanel);
	cpThread.detach();

	std::thread guiThread(&AlarmSystem::Menu, this);
	guiThread.join();
}

void AlarmSystem::Menu()
{
	int choice = 0;
	while(true)
	{ 
		if (m_hgui != nullptr) {
			m_hgui->ShowMenu();
		}
		else {
			std::cerr << "Error: Gui not initialized!" << std::endl;
		}
		
 		if(m_hkeypad != nullptr)
		{
			m_hkeypad->GetUserInput();
		}
		else {
			std::cerr << "Error: KeyPad not initialized!" << std::endl;
		}
		
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}


void AlarmSystem::CreateHardwareDevices(std::vector<std::unique_ptr<IHDevice>>& hardwareSensorDevices, std::vector <std::thread>& threads)
{
	std::vector<SensorData> enumSensorVector;

	TXTDataReader fileConn("HardwareConSens.txt");

	fileConn.ParseData(enumSensorVector);

	for (SensorData& sensor : enumSensorVector)
	{
		hardwareSensorDevices.push_back(HardwareSensorsFactory::CreateObject(sensor));

		threads.emplace_back(&IHSensor::Operate, hardwareSensorDevices.back().get());
		//threads.back().join();
	}

}
void AlarmSystem::checForGUIdevice()
{
	for (auto& sensor : v_hardwareSensorsDevices)
	{
		if (auto* gui = dynamic_cast<HGUI*>(sensor.get()))
		{
			m_hgui = gui;
			break;
		}
	}
}

void AlarmSystem::checkForKeyPadDevice()
{
	for (auto& sensor : v_hardwareSensorsDevices)
	{
		if (auto* keypad = dynamic_cast<HKeyPad*>(sensor.get()))
		{
			m_hkeypad = keypad;
			break;
		}
	}
}
/*void AlarmSystem::RunSimulation()
{
	for (auto& sensor : v_hardwareSensors)
	{
		if (sensor) {
			std::thread sensorThread([sensor]() {
				std::this_thread::sleep_for(std::chrono::seconds(3));
				sensor->Operate();
				});
			sensorThread.detach();
	}
 }*/
