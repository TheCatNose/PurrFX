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

size_t PurrFX::CNesCalculations::dpcm2pcmDataLength(size_t i_nDpcmDataLength)
{
	return i_nDpcmDataLength*8;
}

size_t PurrFX::CNesCalculations::pcm2dpcmDataLength(size_t i_nPcmDataLength)
{
	return i_nPcmDataLength/8;
}

double PurrFX::CNesCalculations::apuPulseFrequency(uint16_t i_nTimer, double i_nCpuClockSpeed)
{
	if (i_nTimer > NesConsts::apuPulseTimerMax)
		i_nTimer = NesConsts::apuPulseTimerMax;
	return i_nCpuClockSpeed/(16.0*(i_nTimer + 1));
}

double PurrFX::CNesCalculations::apuTriangleFrequency(uint16_t i_nTimer, double i_nCpuClockSpeed)
{
	if (i_nTimer > NesConsts::apuTriangleTimerMax)
		i_nTimer = NesConsts::apuTriangleTimerMax;
	return i_nCpuClockSpeed/(32.0*(i_nTimer + 1));
}

uint16_t PurrFX::CNesCalculations::apuPulseTimer(double i_nFrequency, double i_nCpuClockSpeed)
{
	double nTimer = i_nCpuClockSpeed/(16.0*i_nFrequency) - 1;
	if (nTimer > NesConsts::apuPulseTimerMax)
		return   NesConsts::apuPulseTimerMax;
	return uint16_t(nTimer);
}

uint16_t PurrFX::CNesCalculations::apuTriangleTimer(double i_nFrequency, double i_nCpuClockSpeed)
{
	double nTimer = i_nCpuClockSpeed/(32.0*i_nFrequency) - 1;
	if (nTimer > NesConsts::apuTriangleTimerMax)
		return   NesConsts::apuTriangleTimerMax;
	return uint16_t(nTimer);
}

uint16_t PurrFX::CNesCalculations::makeApuPulseTimer(uint8_t i_nRegisterTimerLow, uint8_t i_nRegisterTimerHigh)
{
	return uint16_t(i_nRegisterTimerLow) + ( uint16_t(i_nRegisterTimerHigh & 0b111) << 8 );
}

uint16_t PurrFX::CNesCalculations::makeApuTriangleTimer(uint8_t i_nRegisterTimerLow, uint8_t i_nRegisterTimerHigh)
{
	return uint16_t(i_nRegisterTimerLow) + ( uint16_t(i_nRegisterTimerHigh & 0b111) << 8 );
}

void PurrFX::CNesCalculations::decomposeApuPulseTimer(uint8_t& o_rLowPart, uint8_t& o_rHighPart, uint16_t i_nTimer, uint8_t i_nL)
{
	o_rLowPart  = uint8_t( i_nTimer & 0xFF );
	o_rHighPart = ( (i_nL & 0b11111) << 3) + uint8_t( (i_nTimer >> 8) & 0b111);
}

void PurrFX::CNesCalculations::decomposeApuTriangleTimer(uint8_t& o_rLowPart, uint8_t& o_rHighPart, uint16_t i_nTimer, uint8_t i_nL)
{
	// Same thing
	return decomposeApuPulseTimer(o_rLowPart, o_rHighPart, i_nTimer, i_nL);
}