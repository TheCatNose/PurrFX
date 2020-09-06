#include "CFrameDataConsumer.h"

PurrFX::CFrameDataConsumer::CFrameDataConsumer(size_t i_nSize):
	m_nSize(i_nSize)
{
}

PurrFX::CFrameDataConsumer::~CFrameDataConsumer()
{
}

void PurrFX::CFrameDataConsumer::startFrame()
{
	if (!finished())
		m_bFrameStarted = true;
}

void PurrFX::CFrameDataConsumer::setRegister(ERegister i_eRegister, uint8_t i_nValue)
{
	if (!m_bFrameStarted)
		return;

	m_oData.set(i_eRegister, i_nValue);
}

void PurrFX::CFrameDataConsumer::endFrame()
{
	if (!m_bFrameStarted || finished())
		return;
	m_bFrameStarted = false;

	onFrameDataReady(m_oData);
	m_oData.reset();
	if (m_nSize != UnlimitedSize)
		m_nFramesProcessed++;
}

bool PurrFX::CFrameDataConsumer::finished() const
{
	if (m_nSize == UnlimitedSize)
		return false;
	assert(m_nFramesProcessed <= m_nSize);
	return m_nFramesProcessed == m_nSize; 
}

size_t PurrFX::CFrameDataConsumer::framesProcessed() const
{
	return m_nFramesProcessed;
}
