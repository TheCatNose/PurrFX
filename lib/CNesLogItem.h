#pragma once
// Base class for every type of log item/event

#include "ENesLogItemType.h"

namespace PurrFX
{
	class CNesLogItem
	{
	public:
		virtual ~CNesLogItem();
		virtual ENesLogItemType type() const = 0;
	};
}