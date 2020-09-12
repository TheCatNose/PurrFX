#pragma once

#include <cstdio>
#include <cassert>
#include <vector>
#include <limits>
#include "CDpcmSample.h"
#include "EDpcmFileType.h"
#include "CFile.h"

namespace PurrFX
{
	class CBufferedFileWriter;

	class CDpcmFile
	{
	public:
		static CDpcmSample* load(const pathstring& i_sFileName);
		static bool         save(const CDpcmSample& i_rSample, const pathchar_t* i_sFileName, EDpcmFileType i_eType);

	private:
		static CDpcmSample* loadDmc(CFile& i_rFile, size_t i_nFileSize);
		static CDpcmSample* loadRaw(CFile& i_rFile, size_t i_nFileSize);
		static CDpcmSample* loadWav(CFile& i_rFile, size_t i_nFileSize);

		static void saveAsDmc(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);
		static void saveAsRaw(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);
		static void saveAsWav(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);
	};
}