#pragma once
// Frame data consumer that stores data in memory.
// Also is frame data producer.

#include <vector>
#include <cstddef>
#include <cassert>
#include "DClass.h"
#include "DPath.h"
#include "CFrameDataConsumer.h"
#include "CFrameDataProducerRandomAccess.h"

namespace PurrFX
{
	class CFrameDataBuffer: public CFrameDataConsumer, public CFrameDataProducerRandomAccess
	{
		CLASS_MAKE_NON_COPYABLE(CFrameDataBuffer);
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFrameDataBuffer);
	public:
		CFrameDataBuffer(size_t i_nSize);

		// CFrameDataProducer implementation
		virtual bool       available() const;
		virtual CFrameData get() const;
		virtual bool       next();
	private:
		size_t m_nFrameIndex = 0;

		// CFrameDataProducerRandomAccess implementation
	public:
		virtual size_t     size() const;
		virtual CFrameData getAt(size_t i_nIndex) const;

		// CFrameDataConsumer implementation
	private:
		virtual void onFrameDataReady(const CFrameData& i_rFrameData);

		std::vector<CFrameData> m_aData;
	};
}