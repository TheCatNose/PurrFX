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
