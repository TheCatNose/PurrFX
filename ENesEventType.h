#pragma once

namespace PurrFX
{
	enum class ELogItemType
	{
		CpuInstruction,
		CodeLabel,
		FrameStart,
		FrameEnd,
		ApuRegisterWrite,
	};
}