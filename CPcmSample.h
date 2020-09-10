#pragma once
// Class for audio samples conversion

#include <cstdint>
#include <limits>
#include <cassert>
#include "DClass.h"

namespace PurrFX
{
	class CPcmSample
	{
		typedef long double sample_t;
		explicit CPcmSample(sample_t i_nSample);

	public:
		CPcmSample();

		explicit CPcmSample(uint8_t  i_nValue);
		explicit CPcmSample( int8_t  i_nValue);
		explicit CPcmSample(uint16_t i_nValue);
		explicit CPcmSample( int16_t i_nValue);

		static CPcmSample toMono(const CPcmSample& i_rLeft, const CPcmSample& i_rRight);

		uint8_t  toU8() const;
		 int8_t  toS8() const;
		uint16_t toU16() const;
		 int16_t toS16() const;

	private:
		sample_t m_nSample = 0.0L;
	};
}