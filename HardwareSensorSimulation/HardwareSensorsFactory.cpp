#include "HardwareSensorsFactory.h"
#include "HDoor.h"
#include "HSiren.h"
#include "HSmoke.h"
#include "HWindowBroken.h"

std::unique_ptr<IHSensor> HardwareSensorsFactory::CreateObject(SensorData& sensorData, MessageQueue& messageQueue)
{
	if (sensorData.objType == ObjectTypeEnum::DOOR)
	{
		return std::make_unique<HDoor>(sensorData, messageQueue);
	}
	else if (sensorData.objType == ObjectTypeEnum::SIREN)
	{
		return std::make_unique<HSiren>(sensorData, messageQueue);
	}
	else if (sensorData.objType == ObjectTypeEnum::SMOKE)
	{
		return std::make_unique<HSmoke>(sensorData, messageQueue);
	}
	else if (sensorData.objType == ObjectTypeEnum::WINDOWBROKEN)
	{
		return std::make_unique<HWindowBroken>(sensorData, messageQueue);
	}

	return nullptr;
}