#pragma once
// NES hardware related consts

#include <cstdint>

namespace PurrFX
{
	namespace NesConsts
	{
		/////////
		// DMC //
		/////////

		//                                               [ $4012]
		//                                             11AAAAAAAA000000
		static const uint16_t dpcmSampleAddressMin = 0b1100000000000000;
		static const uint16_t dpcmSampleAddressMax = 0b1111111111000000;
		
		//                                             [ $4013]
		//                                             LLLLLLLL0001
		static const uint16_t dpcmSampleLengthMin  = 0b000000000001;
		static const uint16_t dpcmSampleLengthMax  = 0b111111110001;

		static const int dpcmSampleRate = 33000; // approximate value

		/////////
		// CPU //
		/////////

		static const double cpuClockSpeedNTSC = 1789773.0L;
		static const double cpuClockSpeedPAL  = 1662607.0L;

		///////////
		// Pitch //
		///////////

		static const uint16_t apuPulseTimerMax    = 0b11111111111;
		static const uint16_t apuTriangleTimerMax = 0b11111111111;
	}
}