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
	virtual ~IObserver() = default;
};