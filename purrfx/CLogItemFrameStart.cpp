#include "CLogItemFrameStart.h"

namespace PurrFX
{
	CLogItemFrameStart::CLogItemFrameStart(int i_nFrame):
		m_nFrame(i_nFrame)
	{
		assert(m_nFrame >= 0);
	}

	int CLogItemFrameStart::newFrame() const
	{
		return m_nFrame;
	}

	ELogItemType CLogItemFrameStart::type() const
	{
		return ELogItemType::FrameStart;
	}
}