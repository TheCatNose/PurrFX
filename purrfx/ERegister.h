#pragma once
// Audio related NES registers

namespace PurrFX
{
	enum class ERegister
	{
		Unknown = -1,

		/////////
		// APU //
		/////////

		// Pulse 1
		Apu4000,
		Apu4001,
		Apu4002,
		Apu4003,
		// Pulse 2
		Apu4004,
		Apu4005,
		Apu4006,
		Apu4007,
		// Triangle
		Apu4008,
		Apu400A,
		Apu400B,
		// Noise
		Apu400C,
		Apu400E,
		Apu400F,
		// DMC
		Apu4010,
		Apu4011,
		Apu4012,
		Apu4013,
		// Status
		Apu4015,



		_ENUM_SIZE,
	};

	static const size_t RegisterCount = size_t(ERegister::_ENUM_SIZE);
}