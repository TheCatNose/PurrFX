#pragma once
// Log item for frame end

#include "DClass.h"
#include "CLogItem.h"

namespace PurrFX
{
	class CLogItemFrameEnd: public CLogItem
	{
	public:
		// CLogItem implementation
		virtual ELogItemType type() const;
	private:
		int m_nFrame;
	};
}