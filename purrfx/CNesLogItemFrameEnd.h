#pragma once
// NES log item for frame end

#include <cassert>
#include "DClass.h"
#include "CNesLogItem.h"

namespace PurrFX
{
	class CNesLogItemFrameEnd: public CNesLogItem
	{
	public:
		CNesLogItemFrameEnd(int i_nNewFrame);

		int newFrame() const;

		// CNesLogItem implementation
		virtual ENesLogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesLogItemFrameEnd);
	private:
		int m_nFrame;
	};
}