#pragma once
// WAV writing audio data consumer

#include <cstdint>
#include "DClass.h"
#include "DPath.h"
#include "CAudioDataConsumer.h"
#include "CBufferedFileWriter.h"

namespace PurrFX
{
	class CAudioDataConsumerWavWriter: public CAudioDataConsumer
	{
		CLASS_MAKE_NON_COPYABLE(CAudioDataConsumerWavWriter)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CAudioDataConsumerWavWriter)
	public:
		CAudioDataConsumerWavWriter(const pathstring& i_sFileName, uint32_t i_nDuration);

		// CAudioDataConsumer implementation
		virtual void onStart(const CAudioFormat& i_rAudioFormat, uint32_t i_nBytesToProcess);
		virtual void onData(const char* i_pData, uint32_t i_nSize);
	private:
		CBufferedFileWriter m_oFile;
	};

	typedef CAudioDataConsumerWavWriter CWavWriter;
}