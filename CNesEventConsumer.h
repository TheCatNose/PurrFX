#pragma once
// Base class for all NES events receivers

#include "CNesEvent.h"

namespace PurrFX
{
	class CNesEventConsumer
	{
	public:
		virtual ~CNesEventConsumer();
		
		virtual void onEvent(const CNesEvent* i_pEvent) = 0;
	};
}