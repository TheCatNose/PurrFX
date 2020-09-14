#pragma once
// File writing implementation of NES event consumer class

#include <cstdio>
#include <cassert>
#include <string>
#include "DClass.h"
#include "CNesEventConsumer.h"
#include "CNesEventCpuInstruction.h"
#include "CNesEventCodeLabel.h"
#include "CNesEventFrameStart.h"
#include "CNesEventFrameEnd.h"
#include "CNesEventApuRegisterWrite.h"
#include "CCpuInstructionInfo.h"
#include "CBufferedFileWriter.h"

namespace PurrFX
{
	class CNesEventConsumerFileWriter: public CNesEventConsumer
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesEventConsumerFileWriter)
		CLASS_MAKE_NON_COPYABLE(CNesEventConsumerFileWriter)
	public:
		CNesEventConsumerFileWriter(const pathstring& i_sFileName);

		virtual void onEvent(const CNesEvent* i_pEvent);

	private:
		CBufferedFileWriter m_oFile;
	};
}