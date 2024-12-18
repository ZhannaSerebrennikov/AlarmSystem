#pragma once
#include <iostream>
#include <string>
#include "Logger.h"
#include "../DataHelper/ObjectType.h"

class IObserver {
public:
	virtual void Update(SensorStatusEnum status) = 0;
	/*virtual void Update(SensorStatusEnum status)
	{
		std::cout << "Alarm! Alarm! Alarm! " << std::endl;
	}*/

	virtual ~IObserver() = default;
};