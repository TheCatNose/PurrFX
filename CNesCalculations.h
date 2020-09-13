#pragma once
// NES hardware related calculations

#include <cstdint>
#include <cassert>
#include <cstddef>

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

		// For unpacked length (real size in bytes)
		static bool isDpcmSampleLengthCorrect(size_t i_nSize);
		static uint16_t closestDpcmDataLength(size_t i_nSize);

		static size_t dpcm2pcmDataLength(size_t i_nDpcmDataLength);
		static size_t pcm2dpcmDataLength(size_t i_nPcmDataLength);
	};
}