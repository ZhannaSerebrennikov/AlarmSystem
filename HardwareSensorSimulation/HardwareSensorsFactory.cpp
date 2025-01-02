#include "HardwareSensorsFactory.h"
#include "HDoor.h"
#include "HSiren.h"
#include "HSmoke.h"
#include "HWindowBroken.h"
#include "HMotion.h"

std::unique_ptr<IHSensor> HardwareSensorsFactory::CreateObject(SensorData& sensorData)
{
	if (sensorData.objType == ObjectTypeEnum::DOOR)
	{
		return std::make_unique<HDoor>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::SIREN)
	{
		return std::make_unique<HSiren>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::SMOKE)
	{
		return std::make_unique<HSmoke>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::WINDOWBROKEN)
	{
		return std::make_unique<HWindowBroken>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::MOTION)
	{
		return std::make_unique<HMotion>(sensorData);
	}

	return nullptr;
}