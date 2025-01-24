#pragma once
#include "ObjectType.h"
#include "../AlarmSystem/IObserver.h"
#include <vector>

class MessagePacket {
public:
	void CreatePacket(const SensorData& data, int dst)
	{
		m_sensorData = data;
		m_dstMacAddress = dst;
	}
	void CreatePacket(const std::vector<std::shared_ptr<IObserver>> _activeAlarms, const SensorData& data, int dst)
	{
		m_ActiveAlarms = _activeAlarms;
		m_dstMacAddress = dst;
		m_sensorData = data;
	}

	int GetDstMacAddress()
	{
		return m_dstMacAddress;
	}

	SensorData GetSensorData()
	{
		return m_sensorData;
	}

	std::vector<std::shared_ptr<IObserver>> GetDeviceData()
	{
		return m_ActiveAlarms;
	}

	void IncreaseWasSendTimesCounter()
	{
		m_wasSendTimesCounter = +1;
	}

	void ResetWasSendTimesCounter()
	{
		m_wasSendTimesCounter = 0;
	}

	int GetWasSendTimesCounter()
	{
		return m_wasSendTimesCounter;
	}
	
private:
	int m_dstMacAddress = 0;
	SensorData m_sensorData;
	std::vector<std::shared_ptr<IObserver>> m_ActiveAlarms;

	int m_wasSendTimesCounter = 0;
};