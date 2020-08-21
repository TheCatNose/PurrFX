#include "CAudioDataConsumer.h"

PurrFX::CAudioDataConsumer::CAudioDataConsumer(uint32_t i_nDuration):
	m_nDuration(i_nDuration)
{
	assert(i_nDuration > 0);
}

PurrFX::CAudioDataConsumer::~CAudioDataConsumer()
{
}

bool PurrFX::CAudioDataConsumer::finished() const
{
	return (m_nBytesToProcess == 0);
}

uint32_t PurrFX::CAudioDataConsumer::bytesToProcess() const
{
	return m_nBytesToProcess;
}

void PurrFX::CAudioDataConsumer::start(int i_nSampleRate)
{
	assert(i_nSampleRate > 0);
	m_nBytesToProcess = m_nDuration * i_nSampleRate
		* 2 // stereo
		* 2 // bytes per sample
		;

	onStart(i_nSampleRate, m_nBytesToProcess);
}

void PurrFX::CAudioDataConsumer::processData(const char* i_pData, uint32_t i_nSize)
{
	if (finished())
		return;

	uint32_t nSize = (i_nSize <= m_nBytesToProcess ? i_nSize : m_nBytesToProcess);
	m_nBytesToProcess -= nSize;
	onData(i_pData, nSize);
}