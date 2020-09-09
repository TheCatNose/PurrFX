#pragma once
// Base class for all PCM -> DPCM converters

#include <vector>
#include <cassert>
#include "DClass.h"
#include "CDpcmSample.h"

namespace PurrFX
{
	class CPcm2Dpcm
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CPcm2Dpcm)
		CLASS_MAKE_NON_COPYABLE(CPcm2Dpcm)

	public:
		CPcm2Dpcm(const std::vector<int8_t>& i_rPcmData);

		virtual CDpcmSample* convert() const = 0;

	protected:
		size_t   pcmSize() const;
		uint16_t dpcmSize() const;
		int8_t   pcmByte(size_t i_nIndex) const;

	private:
		size_t                     m_nDpcmSize;
		const std::vector<int8_t>& m_rPcmData;
	};
}