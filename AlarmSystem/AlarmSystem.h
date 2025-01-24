#pragma once
#include <iostream>
#include "Logger.h"
#include "ControlPanel.h"
#include "../HardwareSensorSimulation/HGUI.h"
#include "../HardwareSensorSimulation/HKeyPad.h"
#include "../HardwareSensorSimulation/IHSensor.h"
#include "../HardwareSensorSimulation/HardwareSensorsFactory.h"
#include "../DataHelper/TXTDataReader.h"


class AlarmSystem {
public:
	AlarmSystem();
	void Run();
	void CreateHardwareDevices(std::vector<std::unique_ptr<IHDevice>>& hardwareSensorDevices, std::vector <std::thread>& threads);
	void Menu();
	void RunSimulation();

	~AlarmSystem();

private:
	ControlPanel mainPanel;
	HGUI *m_hgui = nullptr;
	HKeyPad* m_hkeypad = nullptr;
	//std::thread cpThread;
	std::vector<std::unique_ptr<IHDevice>> v_hardwareSensorsDevices;
	std::vector <std::thread> v_threads;

	void checForGUIdevice();
	void checkForKeyPadDevice();
};