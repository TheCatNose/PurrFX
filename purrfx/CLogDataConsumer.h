#pragma once
// Base class for all log data receivers

#include "CLogItem.h"

namespace PurrFX
{
	class CLogDataConsumer
	{
	public:
		virtual ~CLogDataConsumer();
		
		virtual void onNewItem(const CLogItem* i_pLogItem) = 0;
	};
}