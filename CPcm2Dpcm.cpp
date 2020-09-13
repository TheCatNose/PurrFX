#include "CPcm2Dpcm.h"
#include "CNesCalculations.h"
#include "DNesConsts.h"

PurrFX::CPcm2Dpcm::CPcm2Dpcm(const std::vector<uint8_t>& i_rPcmData):
	m_rPcmData(i_rPcmData)
{
	assert(m_rPcmData.size() > 0);
	assert(i_rPcmData.size()%8 == 0);
	size_t nDpcmSize = i_rPcmData.size()/8;
	m_nDpcmSize = CNesCalculations::closestDpcmDataLength(nDpcmSize);
	assert(m_nDpcmSize <= NesConsts::dpcmSampleLengthMax);
}

size_t PurrFX::CPcm2Dpcm::pcmSize() const
{
	return m_nDpcmSize*8;
}

uint16_t PurrFX::CPcm2Dpcm::dpcmSize() const
{
	return uint16_t(m_nDpcmSize);
}

uint8_t PurrFX::CPcm2Dpcm::pcmByte(size_t i_nIndex) const
{
	assert(i_nIndex < pcmSize());
	return m_rPcmData[i_nIndex];
}
