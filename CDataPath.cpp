#include "CDataPath.h"

std::string CDataPath::inputFile(const char* i_sFileName)
{
	return std::string("data/in/") + i_sFileName;
}

std::string CDataPath::outputFile(const char* i_sFileName)
{
	return std::string("data/out/") + i_sFileName;
}
