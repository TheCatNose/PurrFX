#include "CNesLogItemFrameEnd.h"

namespace PurrFX
{
	CNesLogItemFrameEnd::CNesLogItemFrameEnd(int i_nNewFrame):
		m_nFrame(i_nNewFrame)
	{
		assert(m_nFrame >= 0);
	}

	int CNesLogItemFrameEnd::newFrame() const
	{
		return m_nFrame;
	}

	ENesLogItemType CNesLogItemFrameEnd::type() const
	{
		return ENesLogItemType::FrameEnd;
	}
}