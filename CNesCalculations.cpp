#include "CNesCalculations.h"

uint16_t PurrFX::CNesCalculations::dpcmSampleAddressUnpack(uint8_t i_nPackedAddress)
{
	// 11AAAAAA.AA000000
	return (uint16_t(i_nPackedAddress) << 6) + uint16_t(0b1100000000000000);
}

uint8_t PurrFX::CNesCalculations::dpcmSampleAddressPack(uint16_t i_nPackedAddress)
{
	// 11AAAAAA.AA000000
	return uint8_t( (i_nPackedAddress & 0b11111111000000) >> 6);
}

uint16_t PurrFX::CNesCalculations::dpcmSampleLengthUnpack(uint8_t i_nPackedLength)
{
	// LLLL.LLLL0001
	return (uint16_t(i_nPackedLength) << 4) + uint16_t(1);
}

uint8_t PurrFX::CNesCalculations::dpcmSampleLengthPack(uint16_t i_nPackedLength)
{
	// LLLL.LLLL0001
	return uint8_t( (i_nPackedLength & 0b111111110000) >> 4 );
}

bool PurrFX::CNesCalculations::isDpcmSampleLengthCorrect(size_t i_nSize)
{
	if (i_nSize < dpcmSampleLengthUnpack(0x00) ||
		i_nSize > dpcmSampleLengthUnpack(0xFF) )
		return false;

	// %LLLL.LLLL0001 -> 0x01, 0x11, 0x21... 0xFF1
	if ( (i_nSize & 0x01) != 0x01)
		return false;

	return true;
}

uint16_t PurrFX::CNesCalculations::closestDpcmDataLength(size_t i_nSize)
{
	assert(i_nSize > 0);

	if ((i_nSize & 0x1) == 0)
		 i_nSize -= 0x10;

	return (i_nSize & 0xFF0) + 1;
}
