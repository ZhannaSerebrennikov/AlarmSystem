#pragma once
#include <iostream>
#include <string>
#include "Logger.h"
#include "../DataHelper/ObjectType.h"

class IObserver {
public:
	virtual void Update(SensorStatusEnum status) = 0;
	virtual bool IsActive() const = 0;
	virtual void DisplayAlarm() const = 0;
	//virtual std::vector<std::shared_ptr<IObserver>> GetObservers();

	/*virtual void Update(SensorStatusEnum status)
	{
		std::cout << "Alarm! Alarm! Alarm! " << std::endl;
	}*/

	virtual ~IObserver() = default;
};