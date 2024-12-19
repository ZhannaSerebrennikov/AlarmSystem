#include "AlarmSystem.h"

void AlarmSystem::Run()
{
	int choice = 0;

	while (true)
	{
		std::cout << "\n 1. Trigger Sensor\n 2. Remove Alarm\n 3. Display All Alarms\n 4. Display Conected Sensors\n 5.  Exit" << std::endl;
		std::cout << "Enter choice: ";
		std::cin >> choice;
	}
}