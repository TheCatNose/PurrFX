#pragma once
// NES hardware related calculations

#include <cstdint>

namespace PurrFX
{
	class CNesCalculations
	{
	public:
		/////////
		// DMC //
		////////

		static uint16_t dpcmSampleAddressUnpack(uint8_t i_nPackedAddress);
		static uint8_t  dpcmSampleAddressPack(uint16_t i_nPackedAddress);
		static uint16_t dpcmSampleLengthUnpack(uint8_t i_nPackedLength);
		static uint8_t  dpcmSampleLengthPack(uint16_t i_nPackedLength);
	};
}