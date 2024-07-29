#pragma once
#include <mutex>
#include "../DataHelper/ObjectType.h"


class IHSensor {
public:
	virtual ~IHSensor() {}
	virtual void Operate() = 0;
	virtual void ListenToControlPanel() = 0;
};