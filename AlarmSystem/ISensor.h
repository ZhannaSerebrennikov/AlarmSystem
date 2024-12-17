#pragma once
#include "../DataHelper/ObjectType.h"
#include "ISubject.h"
#include <vector>

class ISensor : public ISubject {
public:
	virtual SensorData GetSensorData() const = 0;
	virtual void SetSensorData(SensorData data) = 0;
	//virtual void AddObserver(std::shared_ptr<IObserver>* observer) = 0;
	virtual ObjectTypeEnum GetSensorType() const = 0;
	virtual ~ISensor() {}
protected:
	std::vector<std::shared_ptr<IObserver>> m_observers;
};