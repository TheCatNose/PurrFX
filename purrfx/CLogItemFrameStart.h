#pragma once
// Log item for frame start

#include <cassert>
#include "DClass.h"
#include "CLogItem.h"

namespace PurrFX
{
	class CLogItemFrameStart: public CLogItem
	{
	public:
		CLogItemFrameStart(int i_nFrame);

		int newFrame() const;

		// CLogItem implementation
		virtual ELogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CLogItemFrameStart);
	private:
		int m_nFrame;
	};
}