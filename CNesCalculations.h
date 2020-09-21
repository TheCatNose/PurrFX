#pragma once
// NES hardware related calculations

#include <cstdint>
#include <cassert>
#include <cstddef>
#include "DNesConsts.h"

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

		///////////
		// Pitch //
		///////////

		// APU

		static double   apuPulseFrequency   (uint16_t i_nTimer  , double i_nCpuClockSpeed = NesConsts::cpuClockSpeedNTSC);
		static double   apuTriangleFrequency(uint16_t i_nTimer  , double i_nCpuClockSpeed = NesConsts::cpuClockSpeedNTSC);
		static uint16_t apuPulseTimer       (double i_nFrequency, double i_nCpuClockSpeed = NesConsts::cpuClockSpeedNTSC);
		static uint16_t apuTriangleTimer    (double i_nFrequency, double i_nCpuClockSpeed = NesConsts::cpuClockSpeedNTSC);

		static uint16_t makeApuPulseTimer   (uint8_t i_nRegisterTimerLow, uint8_t i_nRegisterTimerHigh);
		static uint16_t makeApuTriangleTimer(uint8_t i_nRegisterTimerLow, uint8_t i_nRegisterTimerHigh);

		static void decomposeApuPulseTimer   (uint8_t& o_rLowPart, uint8_t& o_rHighPart, uint16_t i_nTimer, uint8_t i_nL = 0x00);
		static void decomposeApuTriangleTimer(uint8_t& o_rLowPart, uint8_t& o_rHighPart, uint16_t i_nTimer, uint8_t i_nL = 0x00);
	};
}
