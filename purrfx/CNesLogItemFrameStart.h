#pragma once
// NES log item for frame end

#include <cassert>
#include "DClass.h"
#include "CNesLogItem.h"

namespace PurrFX
{
	class CNesLogItemFrameStart: public CNesLogItem
	{
	public:
		CNesLogItemFrameStart(int i_nFrame);

		int newFrame() const;

		// CNesLogItem implementation
		virtual ENesLogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesLogItemFrameStart);
	private:
		int m_nFrame;
	};
}