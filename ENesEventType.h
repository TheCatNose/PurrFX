#pragma once

namespace PurrFX
{
	enum class ENesEventType
	{
		CpuInstruction,
		CodeLabel,
		FrameStart,
		FrameEnd,
		ApuRegisterWrite,
	};
}