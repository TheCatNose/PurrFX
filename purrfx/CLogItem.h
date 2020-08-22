#pragma once
// Base class for every type of log item/event

#include "ELogItemType.h"

namespace PurrFX
{
	class CLogItem
	{
	public:
		virtual ~CLogItem();
		virtual ELogItemType type() const = 0;
	};
}