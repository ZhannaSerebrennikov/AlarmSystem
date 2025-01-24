#include "SensorFactory.h"
#include "Door.h"
#include "Siren.h"
#include "Smoke.h"
#include "WindowBroken.h"
#include "Motion.h"
#include "GUI.h"
#include "KeyPad.h"


std::unique_ptr<ISensor> SensorFactory::CreateSensorObject(SensorData& sensorData) {
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
		return std::make_unique<Motion>(sensorData);
	}

	return nullptr;
}

std::unique_ptr<IDevice> SensorFactory::CreateDeviceObject(SensorData& sensorData) {
	if (sensorData.objType == ObjectTypeEnum::GUI)
	{
		return std::make_unique<GUI>(sensorData);
	}
	if (sensorData.objType == ObjectTypeEnum::KEYPAD)
	{
		return std::make_unique<KeyPad>(sensorData);
	}
	return nullptr;
}