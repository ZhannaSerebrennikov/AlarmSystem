#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include "IObserver.h"
#include "../DataHelper/ObjectType.h"
#include "ISensor.h"

class Smoke : public ISensor {
public:
	Smoke(SensorData sensorData);
	SensorData GetSensorData() const override;
	void SetSensorData(SensorData data) override;

	void SetStatus(const SensorStatusEnum& newStatus);
	SensorStatusEnum GetStatus() const;

	ObjectTypeEnum GetSensorType() const override;

	void AddObserver(std::shared_ptr<IObserver> observer) override;
	void RemoveObserver(std::shared_ptr<IObserver> observer) override;
	void NotifyObservers() override;
	const std::vector<std::shared_ptr<IObserver>>& GetObservers() const override;

private:
	SensorData m_sensorData;
	std::atomic<bool> stop;

	std::string m_status;
	//std::vector<std::shared_ptr<IObserver>> m_observers;
};
