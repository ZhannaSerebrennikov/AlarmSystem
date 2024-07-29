#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

#include "TXTDataReader.h"

TXTDataReader::TXTDataReader(const std::string fileName)
{
	m_fileName = fileName;
	m_inFile = std::ifstream(fileName);
}

std::ifstream TXTDataReader::Connection()
{
	std::ifstream fs(m_fileName);
	//m_inFile.open(m_fileName);

	if (!fs.is_open())
	{
		throw std::runtime_error("failed to open ifstream");
	}

	return fs;
}

void TXTDataReader::ParseData(std::vector<SensorData>& hSensorsVector)
{
	std::string line;
	SensorData sensorData;
	std::string firstStr;
	std::string secondStr;
	std::string thirdStr;

	try {
		m_inFile = this->Connection();
	}
	catch (const std::exception& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	while (std::getline(m_inFile, line)) {
		std::istringstream iss(line);

		if (std::getline(iss, firstStr, ':') && std::getline(iss, secondStr, ':') && std::getline(iss, thirdStr, ':'))
		{
			sensorData.objType = ObjectType::ObjectTypeStringToEnum(firstStr);
			sensorData.macAddress = std::stoi(secondStr);
			sensorData.sensorStatus = ObjectType::SensorStatusStringToEnum(thirdStr);
		}
		hSensorsVector.push_back(sensorData);
	}
}

TXTDataReader::~TXTDataReader()
{
	m_inFile.close();
}