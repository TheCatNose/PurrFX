#pragma once

#include <cstdio>
#include <cassert>
#include <vector>
#include "CDpcmSample.h"
#include "EDpcmFileType.h"

namespace PurrFX
{
	class CBufferedFileWriter;

	class CDpcmFile
	{
	public:
		static CDpcmSample* load(const char* i_sFileName);
		static bool         save(const CDpcmSample& i_rSample, const char* i_sFileName, EDpcmFileType i_eType);

	private:
		static CDpcmSample* loadDmc(FILE* i_pFile, size_t i_nFileSize);
		static CDpcmSample* loadRaw(FILE* i_pFile, size_t i_nFileSize);

		static void saveAsDmc(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);
		static void saveAsRaw(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);
	};
}