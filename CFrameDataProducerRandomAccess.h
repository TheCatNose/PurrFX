#pragma once
// Base class for frame data source with random access to it's items

#include "CFrameDataProducer.h"

namespace PurrFX
{
	class CFrameDataProducerRandomAccess: public CFrameDataProducer
	{
	public:
		virtual size_t     size() const = 0;
		virtual CFrameData getAt(size_t i_nIndex) const = 0;
	};
}