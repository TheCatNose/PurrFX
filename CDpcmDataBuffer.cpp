#include "CDpcmDataBuffer.h"

PurrFX::CDpcmDataBuffer::CDpcmDataBuffer(bool i_bUseClassicAccessMode):
	m_oStorage(i_bUseClassicAccessMode)
{
}

bool PurrFX::CDpcmDataBuffer::setCurrentIndex(size_t i_nCurrentIndex)
{
	return m_oStorage.setCurrent(i_nCurrentIndex);
}

size_t PurrFX::CDpcmDataBuffer::size() const
{
	return m_oStorage.size();
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataBuffer::getSample(uint8_t i_nAddress, uint8_t i_nLength) const
{
	return m_oStorage.get(i_nAddress, i_nLength);
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataBuffer::getSample() const
{
	return m_oStorage.get();
}

void PurrFX::CDpcmDataBuffer::onSampleReady(const CDpcmSample& i_rSample)
{
	m_oStorage.add( CDpcmSample::makeCopy(i_rSample) );
}
