#pragma once
// Class optimized for writing many small chunks of data to a file

#include <cstdio>
#include <cassert>
#include <cstring>
#include "DClass.h"
#include "CFile.h"

namespace PurrFX
{
	class CBufferedFileWriter
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CBufferedFileWriter)
		CLASS_MAKE_NON_COPYABLE(CBufferedFileWriter)
	public:
		enum { MIN_BUFFER_SIZE = 4096, MAX_BUFFER_SIZE = 1048576 };

		CBufferedFileWriter(const pathstring& i_sFileName, size_t i_nBufferSize = MIN_BUFFER_SIZE);
		~CBufferedFileWriter();

		bool isOpened() const;
		void write(const void* i_pData, size_t i_nSize);

	private:
		CFile m_oFile;
		
		size_t m_nBufferSize      = 0;
		size_t m_nBufferBytesUsed = 0;
		char*  m_pBuffer          = nullptr;
	};
}