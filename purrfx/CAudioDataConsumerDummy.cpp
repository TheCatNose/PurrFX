#include "CAudioDataConsumerDummy.h"

PurrFX::CAudioDataConsumerDummy::CAudioDataConsumerDummy(uint32_t i_nDuration):
	CAudioDataConsumer(i_nDuration)
{
}

void PurrFX::CAudioDataConsumerDummy::onStart(const CAudioFormat&, uint32_t)
{
}

void PurrFX::CAudioDataConsumerDummy::onData(const char*, uint32_t)
{
}
