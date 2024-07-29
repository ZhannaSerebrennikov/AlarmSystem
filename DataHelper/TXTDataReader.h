#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "ObjectType.h"


class TXTDataReader {
public:
	TXTDataReader(const std::string fileName);
	~TXTDataReader();

	void ParseData(std::vector<SensorData>& hSensorsVector);

private:
	std::string m_fileName;
	std::ifstream m_inFile;

	std::ifstream Connection();
};