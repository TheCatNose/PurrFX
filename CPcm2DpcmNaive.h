#pragma once
// Naive PCM->DPCM converter
//
// Proper implementation should take into account nonstandard signal level changes
// (possible signal level changes for 1bit DPCM are +1 and -1)

#include <limits>
#include "CPcm2Dpcm.h"

namespace PurrFX
{
	class CPcm2DpcmNaive: public CPcm2Dpcm
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CPcm2DpcmNaive)
		CLASS_MAKE_NON_COPYABLE(CPcm2DpcmNaive)
	public:
		CPcm2DpcmNaive(const std::vector<uint8_t>& i_rPcmData);
		virtual CDpcmSample* convert() const;
	};
}