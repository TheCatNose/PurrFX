#pragma once
// File writing implementation of log data consumer class

#include <cstdio>
#include <cassert>
#include <string>
#include "DClass.h"
#include "CLogDataConsumer.h"
#include "CLogItemCpuInstruction.h"
#include "CLogItemCodeLabel.h"
#include "CLogItemFrameStart.h"
#include "CLogItemFrameEnd.h"
#include "CLogItemApuRegisterWrite.h"
#include "CCpuInstructionInfo.h"
#include "CBufferedFileWriter.h"

namespace PurrFX
{
	class CLogFileWriter: public CLogDataConsumer
	{
	public:
		CLogFileWriter(const pathchar_t* i_sFileName);

		virtual void onNewItem(const CLogItem* i_pLogItem);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CLogFileWriter)
		CLASS_MAKE_NON_COPYABLE(CLogFileWriter)
	private:
		CBufferedFileWriter m_oFile;
	};
}