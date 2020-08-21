#include "CAudioDataConsumerDummy.h"

PurrFX::CAudioDataConsumerDummy::CAudioDataConsumerDummy(uint32_t i_nDuration):
	CAudioDataConsumer(i_nDuration)
{
}

void PurrFX::CAudioDataConsumerDummy::onStart(int i_nSampleRate, uint32_t i_nBytesToProcess)
{
}

void PurrFX::CAudioDataConsumerDummy::onData(const char* i_pData, uint32_t i_nSize)
{
}
