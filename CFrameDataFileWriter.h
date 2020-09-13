#pragma once
// Frame data consumer that writes data to a file

#include <cstdint>
#include <array>
#include <algorithm>
#include "DClass.h"
#include "CFrameDataConsumer.h"
#include "CBufferedFileWriter.h"

namespace PurrFX
{
	class CFrameDataFileWriter: public CFrameDataConsumer
	{
		CLASS_MAKE_NON_COPYABLE(CFrameDataFileWriter)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFrameDataFileWriter)
	public:
		CFrameDataFileWriter(const pathstring& i_sFileName, size_t i_nSize = UnlimitedSize);

	private:
		// CFrameDataConsumer implementation
		virtual void onFrameDataReady(const CFrameData& i_rFrameData);

		CBufferedFileWriter m_oFile;
	};
}