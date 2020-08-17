#include "CNesLogItemFrameStart.h"

namespace PurrFX
{
	CNesLogItemFrameStart::CNesLogItemFrameStart(int i_nFrame):
		m_nFrame(i_nFrame)
	{
		assert(m_nFrame >= 0);
	}

	int CNesLogItemFrameStart::newFrame() const
	{
		return m_nFrame;
	}

	ENesLogItemType CNesLogItemFrameStart::type() const
	{
		return ENesLogItemType::FrameStart;
	}
}