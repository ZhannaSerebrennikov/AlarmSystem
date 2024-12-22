#pragma once
#include <iostream>
#include "Logger.h"
#include "ControlPanel.h"
#include "../HardwareSensorSimulation/IHSensor.h"
#include "../HardwareSensorSimulation/HardwareSensorsFactory.h"
#include "../DataHelper/TXTDataReader.h"


class AlarmSystem {
public:
	AlarmSystem();
	void Run();
	void CreateHardwareDevices(std::vector<std::unique_ptr<IHSensor>>& hardwareSensorDevices, std::vector <std::thread>& threads);
	void ShowMenu();

	~AlarmSystem();

private:
	ControlPanel mainPanel;
	//std::thread cpThread;
	std::vector<std::unique_ptr<IHSensor>> v_hardwareSensors;
	std::vector <std::thread> v_threads;

};