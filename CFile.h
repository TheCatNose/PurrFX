#pragma once
// Basic cross-platform file object and API wrapper

#include <cstdio>
#include "DPath.h"
#include "DClass.h"

namespace PurrFX
{
	class CFile
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFile)
		CLASS_MAKE_NON_COPYABLE(CFile)
	public:
		enum EMode
		{
			Read,
			Write,
		};

		CFile(const pathstring& i_sPath, EMode i_eMode);
		~CFile();

		size_t read(void* o_pBuffer, size_t i_nBytes);
		size_t write(const void* i_pBuffer, size_t i_nBytes);
		bool isOpened() const;
		size_t size() const;
		operator FILE*() const;

	private:
		FILE* m_pFile = nullptr;
	};
}