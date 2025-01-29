#pragma once
#include "ObjectType.h"
#include "../AlarmSystem/IObserver.h"
#include "../AlarmSystem/GUI.h"
#include <vector>

class MessagePacket {
public:
	void CreatePacket(const SensorData& data, int dst)
	{
		m_sensorData = data;
		m_dstMacAddress = dst;
	}
	void CreatePacket(const GUIData& _guidata, const SensorData& data, int dst)
	{
		m_guiData = _guidata;
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
		return m_guiData.activeAlarms;
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

	GUIData GetGuiData()
	{
		return m_guiData;
	}
	
private:
	int m_dstMacAddress = 0;
	SensorData m_sensorData;
	GUIData m_guiData;

	int m_wasSendTimesCounter = 0;
};