#include "CNesEventFrameEnd.h"

namespace PurrFX
{
	ENesEventType CNesEventFrameEnd::type() const
	{
		return ENesEventType::FrameEnd;
	}
}