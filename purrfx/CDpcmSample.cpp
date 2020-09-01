#include "CDpcmSample.h"
#include "CNesCalculations.h"
#include "DNesConsts.h"

PurrFX::CDpcmSample::CDpcmSample(uint8_t i_nAddress, uint8_t i_nLength):
	m_nDpcmAddress(i_nAddress)
{
	m_aData.resize(CNesCalculations::dpcmSampleLengthUnpack(i_nLength), 0);
	assert(m_aData.size() >= NesConsts::dpcmSampleLengthMin &&
		   m_aData.size() <= NesConsts::dpcmSampleLengthMax );
}

uint8_t PurrFX::CDpcmSample::dpcmAddress() const
{
	return m_nDpcmAddress;
}

uint8_t PurrFX::CDpcmSample::dpcmLength() const
{
	size_t nSize = m_aData.size();
	assert(nSize >= NesConsts::dpcmSampleLengthMin &&
		   nSize <= NesConsts::dpcmSampleLengthMax );
	return CNesCalculations::dpcmSampleLengthPack( uint16_t(nSize) );
}

bool PurrFX::CDpcmSample::set(size_t i_nByteIndex, uint8_t i_nValue)
{
	if (i_nByteIndex >= m_aData.size())
		return false;
	m_aData[i_nByteIndex] = i_nValue;
	return true;
}

void PurrFX::CDpcmSample::set(const uint8_t* i_pData)
{
	std::copy(i_pData, i_pData + m_aData.size(), m_aData.begin());
}

uint8_t PurrFX::CDpcmSample::get(size_t i_nByteIndex) const
{
	assert(i_nByteIndex < m_aData.size());
	return m_aData[i_nByteIndex];
}

uint16_t PurrFX::CDpcmSample::size() const
{
	assert(m_aData.size() <= UINT16_MAX);
	return uint16_t(m_aData.size());
}

const uint8_t* PurrFX::CDpcmSample::data() const
{
	return m_aData.data();
}
