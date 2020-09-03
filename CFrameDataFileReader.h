#pragma once
// File loading implementation of frame data source

#include <cstdio>
#include <cstdint>
#include <cassert>
#include "DClass.h"
#include "CFile.h"
#include "CFrameDataProducerRandomAccess.h"

namespace PurrFX
{
	class CFrameDataFileReader: public CFrameDataProducerRandomAccess
	{
	public:
		CFrameDataFileReader(const pathstring& i_sFileName);
		~CFrameDataFileReader();

		// CFrameDataProducer implementation
		virtual bool       available() const;
		virtual CFrameData get() const;
		virtual bool       next();

		// CFrameDataProducerRandomAccess implementation
		virtual size_t     size() const;
		virtual CFrameData getAt(size_t i_nIndex) const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFrameDataFileReader)
		CLASS_MAKE_NON_COPYABLE(CFrameDataFileReader)
	private:
		CFrameData* m_pData = nullptr;
		size_t      m_nDataItems = 0;
		size_t      m_nDataItemCurrentIndex = 0;
	};
}