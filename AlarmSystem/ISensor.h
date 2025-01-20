#pragma once
#include "../DataHelper/ObjectType.h"
#include "ISubject.h"
#include "IDevice.h"
#include <vector>

class ISensor : public ISubject, public IDevice {
public:
	virtual void SetSensorData(SensorData data) = 0;
	//SensorData GetSensorData() const override = 0;
	virtual const std::vector<std::shared_ptr<IObserver>>& GetObservers() const = 0;
	//virtual void AddObserver(std::shared_ptr<IObserver>* observer) = 0;
	virtual ObjectTypeEnum GetSensorType() const = 0;
	virtual ~ISensor() = default;
protected:
	std::vector<std::shared_ptr<IObserver>> m_observers;
};