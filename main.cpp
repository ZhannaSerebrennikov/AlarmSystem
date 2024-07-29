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


//std::mutex HDoor::m_mtx;
//std::mutex HSiren::m_mtx;
//std::mutex HSmoke::m_mtx;
//std::mutex HWindowBroken::m_mtx;

void CreateHardwareDevices(std::vector<std::unique_ptr<IHSensor>>& hardwareSensorDevices, std::vector <std::thread>& threads, MessageQueue& messageQueue)
{
	std::vector<SensorData> enumSensorVector;

	TXTDataReader fileConn("HardwareConSens.txt");

	fileConn.ParseData(enumSensorVector);

	for (SensorData& sensor : enumSensorVector)
	{
		hardwareSensorDevices.push_back(HardwareSensorsFactory::CreateObject(sensor, messageQueue));
		threads.emplace_back(&IHSensor::Operate, hardwareSensorDevices.back().get());
	}

}


int main()
{
	std::vector<std::unique_ptr<IHSensor>> v_hardwareSensors;
	MessageQueue messageQueue;

	ControlPanel mainPanel(messageQueue);
	std::thread cpThread(&ControlPanel::Start, &mainPanel);

	std::vector <std::thread> v_threads;

	CreateHardwareDevices(v_hardwareSensors, v_threads, messageQueue);

	cpThread.join();

	for (auto& thread : v_threads) {
		
		thread.join();
	}

	return 0;
}