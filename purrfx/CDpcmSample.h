#pragma once

#include <cstdint>
#include <vector>
#include <cassert>
#include "DClass.h"

namespace PurrFX
{
	class CDpcmSample
	{
	public:
		CDpcmSample(uint8_t i_nAddress, uint8_t i_nLength);

		uint8_t dpcmAddress() const;
		uint8_t dpcmLength() const;

		bool                 set(size_t i_nByteIndex, uint8_t i_nValue);
		size_t               size() const;
		const uint8_t* const data() const;

		CLASS_MAKE_NON_COPYABLE(CDpcmSample)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmSample)
	private:
		uint8_t m_nDpcmAddress;
		std::vector<uint8_t> m_aData;
	};
}
