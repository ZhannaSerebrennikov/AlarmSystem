#include "AlarmSystem.h"

AlarmSystem::AlarmSystem()
{
	Logger::GetInstance().OpenLogFile("LogFile.txt");
	
}

AlarmSystem::~AlarmSystem()
{
	Logger::GetInstance().CloseLogFile();
}

void AlarmSystem::Run()
{
	while (true)
	{
		CreateHardwareDevices(v_hardwareSensors, v_threads);
		std::thread cpThread(&ControlPanel::Start, &mainPanel);
		std::thread guiThread(&AlarmSystem::ShowMenu, this);

		//cpThread.join();

		for (auto& thread : v_threads) {

			thread.join();
		}

		cpThread.detach();
		guiThread.detach();
	}

}

void AlarmSystem::ShowMenu()
{
	int choice = 0;
	while(true)
	{ 
		std::cout << "\n 1. Trigger Sensor\n 2. Remove Alarm\n 3. Display All Alarms\n 4. Display Conected Sensors\n 5.  Exit" << std::endl;
		std::cout << "Enter choice: ";
		std::cin >> choice;

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}


void AlarmSystem::CreateHardwareDevices(std::vector<std::unique_ptr<IHSensor>>& hardwareSensorDevices, std::vector <std::thread>& threads)
{
	std::vector<SensorData> enumSensorVector;

	TXTDataReader fileConn("HardwareConSens.txt");

	fileConn.ParseData(enumSensorVector);

	for (SensorData& sensor : enumSensorVector)
	{
		hardwareSensorDevices.push_back(HardwareSensorsFactory::CreateObject(sensor));
		threads.emplace_back(&IHSensor::Operate, hardwareSensorDevices.back().get());
	}

}

