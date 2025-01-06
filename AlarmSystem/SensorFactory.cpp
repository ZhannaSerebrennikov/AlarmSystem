
#include "SensorFactory.h"
#include "Door.h"
#include "Siren.h"
#include "Smoke.h"
#include "WindowBroken.h"

std::unique_ptr<ISensor> SensorFactory::CreateObject(SensorData& sensorData) {
	if (sensorData.objType == ObjectTypeEnum::DOOR)
	{
		return std::make_unique<Door>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::SIREN)
	{
		return std::make_unique<Siren>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::SMOKE)
	{
		return std::make_unique<Smoke>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::WINDOWBROKEN)
	{
		return std::make_unique<WindowBroken>(sensorData);
	}
	else if (sensorData.objType == ObjectTypeEnum::MOTION)
	{
		return std::make_unique<Siren>(sensorData);
	}

	return nullptr;
}