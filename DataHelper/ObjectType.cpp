#include <map>
#include <string>
#include <stdexcept> 
#include "ObjectType.h"

ObjectTypeEnum ObjectType::ObjectTypeStringToEnum(const std::string& str)
{
	static const std::map<std::string, ObjectTypeEnum> objTypeMap = {
		{"Door", ObjectTypeEnum::DOOR},
		{"Smoke", ObjectTypeEnum::SMOKE},
		{"Siren", ObjectTypeEnum::SIREN},
		{"WindowBroken", ObjectTypeEnum::WINDOWBROKEN},
		{"Motion", ObjectTypeEnum::MOTION},
		{"GUI", ObjectTypeEnum::GUI},
		{"KEYPAD", ObjectTypeEnum::KEYPAD}

	};

	auto it = objTypeMap.find(str);

	if (it != objTypeMap.end())
	{
		return it->second;
	}
	else {
		// Handle the case where the string doesn't match any enum value
		throw std::invalid_argument("Invalid enum string");
	}
}

SensorStatusEnum ObjectType::SensorStatusStringToEnum(const std::string& str)
{
	static const std::map<std::string, SensorStatusEnum> sensStatusMap = {
		{"Alarm", SensorStatusEnum::ALARM},
		{"Ok", SensorStatusEnum::OK},
		{"Missing", SensorStatusEnum::MISSING}
	};

	auto it = sensStatusMap.find(str);

	if (it != sensStatusMap.end())
	{
		return it->second;
	}
	else {
		// Handle the case where the string doesn't match any enum value
		throw std::invalid_argument("Invalid enum string");
	}
}

std::string ObjectType::SensorStatusEnumToString(const SensorStatusEnum enm)
{
	static const std::map<SensorStatusEnum, std::string> sensStatusMap = {
		{SensorStatusEnum::ALARM, "Alarm"},
		{SensorStatusEnum::OK, "Ok"},
		{SensorStatusEnum::MISSING, "Missing"}
	};

	auto it = sensStatusMap.find(enm);

	if (it != sensStatusMap.end())
	{
		return it->second;
	}
	else {
		// Handle the case where the string doesn't match any enum value
		throw std::invalid_argument("Invalid enum string");
	}
}