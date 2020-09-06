#include "CFrameDataBuffer.h"

PurrFX::CFrameDataBuffer::CFrameDataBuffer(size_t i_nSize):
	CFrameDataConsumer(i_nSize)
{
	assert(i_nSize > 0);
	m_aData.resize(i_nSize);
}

bool PurrFX::CFrameDataBuffer::available() const
{
	return m_nFrameIndex < m_aData.size();
}

PurrFX::CFrameData PurrFX::CFrameDataBuffer::get() const
{
	assert(available());
	return m_aData[m_nFrameIndex];
}

bool PurrFX::CFrameDataBuffer::next()
{
	if (m_nFrameIndex >= m_aData.size()-1)
		return false;
	m_nFrameIndex++;
	return true;
}

size_t PurrFX::CFrameDataBuffer::size() const
{
	return m_aData.size();
}

PurrFX::CFrameData PurrFX::CFrameDataBuffer::getAt(size_t i_nIndex) const
{
	assert(i_nIndex < size());
	return m_aData[i_nIndex];
}

void PurrFX::CFrameDataBuffer::onFrameDataReady(const CFrameData& i_rFrameData)
{
	m_aData[framesProcessed()] = i_rFrameData;
}
