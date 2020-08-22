#pragma once

#include <cstdint>
#include <cassert>
#include "DClass.h"

namespace PurrFX
{
	class CCpuInstructionInfo
	{
	public:
		CCpuInstructionInfo(uint8_t i_nOpcode);

		const char* name() const;
		int argBytes() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CCpuInstructionInfo)
	private:
		uint8_t m_nOpcode;
	};
}