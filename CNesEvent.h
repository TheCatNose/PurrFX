#pragma once
// Base class for every type of NES event

#include "ENesEventType.h"

namespace PurrFX
{
	class CNesEvent
	{
	public:
		virtual ~CNesEvent();
		virtual ENesEventType type() const = 0;
	};
}