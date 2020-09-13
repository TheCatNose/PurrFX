#pragma once

#include <cstdint>
#include <cassert>
#include "DClass.h"

namespace PurrFX
{
	class CCpuInstructionInfo
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CCpuInstructionInfo)
	public:
		CCpuInstructionInfo(uint8_t i_nOpcode);

		const char* name() const;
		int argBytes() const;

	private:
		uint8_t m_nOpcode;
	};
}