#pragma once
// NES log item for frame end

#include "DClass.h"
#include "CNesLogItem.h"

namespace PurrFX
{
	class CNesLogItemFrameEnd: public CNesLogItem
	{
	public:
		// CNesLogItem implementation
		virtual ENesLogItemType type() const;
	private:
		int m_nFrame;
	};
}