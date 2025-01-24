#pragma once
#include "IDevice.h"

class KeyPad : public IDevice
{
private:
	SensorData m_sensorData;
public:
	KeyPad(SensorData _sensorData);
	SensorData GetSensorData() const;
	void SetSensorData(SensorData data);
	void SetStatus(const SensorStatusEnum& newStatus);
	int GetUserInput();
	//const std::vector<std::shared_ptr<IObserver>> GetData() { return {}; }
};
