#pragma once
// Base class for all frame data sources

#include "CFrameData.h"

namespace PurrFX
{
	class CFrameDataProducer
	{
	public:
		virtual ~CFrameDataProducer();
		
		virtual bool       available() const = 0;
		virtual CFrameData get() const = 0;
		virtual bool       next() = 0;
	};
}