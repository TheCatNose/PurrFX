#pragma once

#include <string>

class CDataPath
{
public:
	static std::string inputFile(const char* i_sFileName);
	static std::string outputFile(const char* i_sFileName);
};
