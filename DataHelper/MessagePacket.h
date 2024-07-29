#pragma once
#include "ObjectType.h"

class MessagePacket {
public:
	void CreatePacket(const SensorData& data, int dst)
	{
		m_sensorData = data;
		m_dstMacAddress = dst;
	}
	int GetDstMacAddress()
	{
		return m_dstMacAddress;
	}

	SensorData GetSensorData()
	{
		return m_sensorData;
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
	int m_dstMacAddress;
	SensorData m_sensorData;

	int m_wasSendTimesCounter = 0;
};