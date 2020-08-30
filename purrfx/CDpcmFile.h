#pragma once

#include <cstdio>
#include <cassert>
#include <vector>
#include "CDpcmSample.h"

namespace PurrFX
{
	class CDpcmFile
	{
	public:
		static CDpcmSample* load(const char* i_sFileName);

	private:
		static CDpcmSample* loadDmc(FILE* i_pFile, size_t i_nFileSize);
		static CDpcmSample* loadRaw(FILE* i_pFile, size_t i_nFileSize);
	};
}