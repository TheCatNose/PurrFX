#pragma once

#include <cstdint>
#include <cassert>
#include "DClass.h"

namespace PurrFX
{
	class CNesCpuInstructionInfo
	{
	public:
		CNesCpuInstructionInfo(uint8_t i_nOpcode);

		const char* name() const;
		int argBytes() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesCpuInstructionInfo)
	private:
		uint8_t m_nOpcode;
	};
}