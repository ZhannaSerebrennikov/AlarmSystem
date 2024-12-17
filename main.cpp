#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "AlarmSystem/ControlPanel.h"
#include "HardwareSensorSimulation/IHSensor.h"
#include "HardwareSensorSimulation/HardwareSensorsFactory.h"
#include "DataHelper/TXTDataReader.h"
#include "HardwareSensorSimulation/HDoor.h"
#include "HardwareSensorSimulation//HSiren.h"
#include "HardwareSensorSimulation/HSmoke.h"
#include "HardwareSensorSimulation/HWindowBroken.h"
#include "AlarmSystem/Door.h"
#include "AlarmSystem/Logger.h"

//std::mutex HDoor::m_mtx;
//std::mutex HSiren::m_mtx;
//std::mutex HSmoke::m_mtx;
//std::mutex HWindowBroken::m_mtx;

void CreateHardwareDevices(std::vector<std::unique_ptr<IHSensor>>& hardwareSensorDevices, std::vector <std::thread>& threads)
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


int main()
{
	std::vector<std::unique_ptr<IHSensor>> v_hardwareSensors;

	Logger::GetInstance().OpenLogFile("LogFile.txt");
	//MessageQueue messageQueue;

	ControlPanel mainPanel;
	std::thread cpThread(&ControlPanel::Start, &mainPanel);

	std::vector <std::thread> v_threads;

	CreateHardwareDevices(v_hardwareSensors, v_threads);

	cpThread.join();

	for (auto& thread : v_threads) {
		
		thread.join();
	}

	Logger::GetInstance().CloseLogFile();

	return 0;
}