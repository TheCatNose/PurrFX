#pragma once
// DPCM data source.
// Must own all samples.

#include "CDpcmSample.h"

namespace PurrFX
{
	class CDpcmDataProvider
	{
	public:
		virtual ~CDpcmDataProvider();

		// [ Classic access mode ]
		// Must return sample by address&length pair (as it happens in NSF code)
		virtual const CDpcmSample* getSample(uint8_t i_nAddress, uint8_t i_nLength) const = 0;

		// [ Modern access mode ]
		// Must return currently selected sample
		virtual const CDpcmSample* getSample() const = 0;
	};
}