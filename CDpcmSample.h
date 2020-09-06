#pragma once

#include <cstdint>
#include <vector>
#include <cassert>
#include <algorithm>
#include "DClass.h"

namespace PurrFX
{
	class CDpcmSample
	{
	public:
		CDpcmSample(uint8_t i_nAddress, uint8_t i_nLength);
		static CDpcmSample* makeCopy(const CDpcmSample& i_rSample);

		uint8_t dpcmAddress() const;
		uint8_t dpcmLength() const;

		bool           set(size_t i_nByteIndex, uint8_t i_nValue);
		void           set(const uint8_t* i_pData);
		uint8_t        get(size_t i_nByteIndex) const;
		uint16_t       size() const;
		const uint8_t* data() const;

		CLASS_MAKE_NON_COPYABLE(CDpcmSample)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmSample)
	private:
		uint8_t m_nDpcmAddress;
		std::vector<uint8_t> m_aData;
	};
}
