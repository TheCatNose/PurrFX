#pragma once
// Base class for all log data receivers

#include "CNesLogItem.h"

namespace PurrFX
{
	class CNesLogDataConsumer
	{
	public:
		virtual ~CNesLogDataConsumer();
		
		virtual void onNewItem(const CNesLogItem* i_pLogItem) = 0;
	};
}