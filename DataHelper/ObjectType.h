#pragma once
#include <string>

enum class ObjectTypeEnum {
	DOOR,
	SMOKE,
	SIREN,
	WINDOWBROKEN,
	MOTION,
	GUI,
	KEYPAD
};

enum class SensorStatusEnum {
	OK = 0,
	ALARM = 1,
	MISSING = 2
};

struct SensorData {
	ObjectTypeEnum objType;
	SensorStatusEnum sensorStatus;
	int macAddress;
	int inputOutput;
};


class ObjectType {
public:
	static ObjectTypeEnum ObjectTypeStringToEnum(const std::string& str);

	static SensorStatusEnum SensorStatusStringToEnum(const std::string& str);
	static std::string SensorStatusEnumToString(const SensorStatusEnum enm);
};