#pragma once
// Dummy audio data consumer (does nothing with incoming data)

#include <cstdint>
#include "DClass.h"
#include "CAudioDataConsumer.h"

namespace PurrFX
{
	class CAudioDataConsumerDummy: public CAudioDataConsumer
	{
	public:
		CAudioDataConsumerDummy(uint32_t i_nDuration = CAudioDataConsumer::InfiniteDuration);

		// CAudioDataConsumer implementation
		virtual void onStart(const CAudioFormat& i_rAudioFormat, uint32_t i_nBytesToProcess);
		virtual void onData(const char* i_pData, uint32_t i_nSize);

		CLASS_MAKE_NON_COPYABLE(CAudioDataConsumerDummy)
	};
}