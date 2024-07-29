#pragma once
#include <string>

enum class ObjectTypeEnum {
	DOOR,
	SMOKE,
	SIREN,
	WINDOWBROKEN
};

enum class SensorStatusEnum {
	OK,
	ALARM,
	MISSING
};

struct SensorData {
	ObjectTypeEnum objType;
	int macAddress;
	SensorStatusEnum sensorStatus;
};


class ObjectType {
public:
	static ObjectTypeEnum ObjectTypeStringToEnum(const std::string& str);

	static SensorStatusEnum SensorStatusStringToEnum(const std::string& str);
};