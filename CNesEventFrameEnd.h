#pragma once
// NES event: frame end

#include "DClass.h"
#include "CNesEvent.h"

namespace PurrFX
{
	class CNesEventFrameEnd: public CNesEvent
	{
	public:
		// CNesEvent implementation
		virtual ENesEventType type() const;
	private:
		int m_nFrame;
	};
}