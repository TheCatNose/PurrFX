#include "CDpcmStorage.h"

PurrFX::CDpcmStorage::CDpcmStorage(bool i_bUseClassicAccessMode)
{
	m_bUseClassicAccessMode = i_bUseClassicAccessMode;
}

PurrFX::CDpcmStorage::~CDpcmStorage()
{
	for (auto* pSample: m_aSamples)
		delete pSample;
}

void PurrFX::CDpcmStorage::add(CDpcmSample* i_pSample)
{
	m_aSamples.push_back(i_pSample);

	if (m_bUseClassicAccessMode)
	{
		uint16_t nKey = key(i_pSample->dpcmAddress(), i_pSample->dpcmLength());
		m_mSamples[nKey] = i_pSample;
	}
}

size_t PurrFX::CDpcmStorage::size() const
{
	return m_aSamples.size();
}

bool PurrFX::CDpcmStorage::setCurrent(size_t i_nIndex)
{
	if (i_nIndex >= m_aSamples.size())
		return false;
	m_nCurrentIndex = i_nIndex;
	m_bIsCurrentIndexSet = true;
	return true;
}

const PurrFX::CDpcmSample* PurrFX::CDpcmStorage::get(uint8_t i_nAddress, uint8_t i_nLength) const
{
	if (!m_bUseClassicAccessMode)
		return nullptr;

	uint16_t nKey = key(i_nAddress, i_nLength);
	std::map<uint16_t, CDpcmSample*>::const_iterator iSample = m_mSamples.find(nKey);
	if (iSample == m_mSamples.cend())
		return nullptr;
	return iSample->second;
}

const PurrFX::CDpcmSample* PurrFX::CDpcmStorage::get() const
{
	if (m_bIsCurrentIndexSet &&
		m_nCurrentIndex < m_aSamples.size())
		return m_aSamples[m_nCurrentIndex];
	return nullptr;
}

const bool PurrFX::CDpcmStorage::del(size_t i_nIndex)
{
	if (i_nIndex >= m_aSamples.size())
		return false;

	CDpcmSample* pDelSample = m_aSamples[i_nIndex];
	uint16_t nDelKey = key(pDelSample->dpcmAddress(), pDelSample->dpcmLength());
	delete pDelSample;
	
	m_aSamples.erase( m_aSamples.begin()+i_nIndex );
	if (m_bUseClassicAccessMode)
	{
		assert(m_mSamples.count(nDelKey) == 1);
		m_mSamples.erase(nDelKey);
		for (auto iSample = m_mSamples.cbegin(); iSample != m_mSamples.cend(); iSample++)
		{
			// Find replacement
			CDpcmSample* pSample = iSample->second;
			if (key(pSample->dpcmAddress(), pSample->dpcmLength()) == nDelKey)
			{
				m_mSamples[nDelKey] = pSample;
				break;
			}
		}
	}

	if (m_nCurrentIndex >= m_aSamples.size())
		m_bIsCurrentIndexSet = false;

	return true;
}

uint16_t PurrFX::CDpcmStorage::key(uint8_t i_nAddress, uint8_t i_nLength) const
{
	return i_nAddress + ( uint16_t(i_nLength) << 8 );
}