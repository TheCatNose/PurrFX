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

void PurrFX::CAudioDataConsumer::start(const CAudioFormat& i_rAudioFormat)
{
	m_nBytesToProcess = m_nDuration
		* i_rAudioFormat.sampleRate()
		* i_rAudioFormat.channels()
		* i_rAudioFormat.bytesPerSample();

	onStart(i_rAudioFormat, m_nBytesToProcess);
}

void PurrFX::CAudioDataConsumer::processData(const char* i_pData, uint32_t i_nSize)
{
	if (finished())
		return;

	uint32_t nSize = (i_nSize <= m_nBytesToProcess ? i_nSize : m_nBytesToProcess);
	m_nBytesToProcess -= nSize;
	onData(i_pData, nSize);
}