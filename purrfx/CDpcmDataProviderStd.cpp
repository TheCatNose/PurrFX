#include "CDpcmDataProviderStd.h"

PurrFX::CDpcmDataProviderStd::CDpcmDataProviderStd(bool i_bEnableClassicAccessMode):
	m_bClassicAccessModeEnabled(i_bEnableClassicAccessMode)
{
}

PurrFX::CDpcmDataProviderStd::~CDpcmDataProviderStd()
{
	for (auto* pSample: m_aSamples)
		delete pSample;
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataProviderStd::getSample(uint8_t i_nAddress, uint8_t i_nLength) const
{
	if (!m_bClassicAccessModeEnabled)
		return nullptr;

	uint16_t nKey = key(i_nAddress, i_nLength);
	std::map<uint16_t, CDpcmSample*>::const_iterator iSample = m_mSamples.find(nKey);
	if (iSample == m_mSamples.cend())
		return nullptr;
	return iSample->second;
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataProviderStd::getSample() const
{
	if (m_bIsCurrentIndexSet &&
		m_nCurrentIndex < m_aSamples.size())
		return m_aSamples[m_nCurrentIndex];
	return nullptr;
}


bool PurrFX::CDpcmDataProviderStd::setCurrentIndex(size_t i_nCurrentIndex)
{
	if (i_nCurrentIndex >= m_aSamples.size())
		return false;
	m_nCurrentIndex = i_nCurrentIndex;
	m_bIsCurrentIndexSet = true;
	return true;
}

size_t PurrFX::CDpcmDataProviderStd::size() const
{
	return m_aSamples.size();
}

void PurrFX::CDpcmDataProviderStd::add(CDpcmSample* i_pSample)
{
	m_aSamples.push_back(i_pSample);

	if (m_bClassicAccessModeEnabled)
	{
		uint16_t nKey = key(i_pSample->dpcmAddress(), i_pSample->dpcmLength());
		m_mSamples[nKey] = i_pSample;
	}
}

bool PurrFX::CDpcmDataProviderStd::del(size_t i_nCurrentIndex)
{
	if (i_nCurrentIndex >= m_aSamples.size())
		return false;

	delete m_aSamples[i_nCurrentIndex];
	m_aSamples.erase( m_aSamples.begin()+i_nCurrentIndex );
	return true;
}

uint16_t PurrFX::CDpcmDataProviderStd::key(uint8_t i_nAddress, uint8_t i_nLength) const
{
	return i_nAddress + ( uint16_t(i_nLength) << 8 );
}
