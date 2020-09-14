#pragma once
// NES event: frame start

#include <cassert>
#include "DClass.h"
#include "CNesEvent.h"

namespace PurrFX
{
	class CNesEventFrameStart: public CNesEvent
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesEventFrameStart)
	public:
		CNesEventFrameStart(int i_nFrame);

		int newFrame() const;

		// CNesEvent implementation
		virtual ENesEventType type() const;

	private:
		int m_nFrame;
	};
}