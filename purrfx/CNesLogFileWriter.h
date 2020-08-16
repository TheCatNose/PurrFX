#pragma once
// File writing implementation of log data consumer class

#include <cstdio>
#include <cassert>
#include <string>
#include "DClass.h"
#include "CNesLogDataConsumer.h"
#include "CNesLogItemCpuInstruction.h"
#include "CNesLogItemCodeLabel.h"
#include "CNesCpuInstructionInfo.h"
#include "CBufferedFileWriter.h"

namespace PurrFX
{
	class CNesLogFileWriter: public CNesLogDataConsumer
	{
	public:
		CNesLogFileWriter(const char* i_sFileName);

		virtual void onNewItem(const CNesLogItem* i_pLogItem);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesLogFileWriter)
		CLASS_MAKE_NON_COPYABLE(CNesLogFileWriter)
	private:
		CBufferedFileWriter m_oFile;
	};
}