#include "CNesEventFrameStart.h"

namespace PurrFX
{
	CNesEventFrameStart::CNesEventFrameStart(int i_nFrame):
		m_nFrame(i_nFrame)
	{
		assert(m_nFrame >= 0);
	}

	int CNesEventFrameStart::newFrame() const
	{
		return m_nFrame;
	}

	ENesEventType CNesEventFrameStart::type() const
	{
		return ENesEventType::FrameStart;
	}
}