#include "CDpcmDataFileReader.h"

PurrFX::CDpcmDataFileReader::CDpcmDataFileReader(bool i_bEnableClassicAccessMode):
	m_bClassicAccessModeEnabled(i_bEnableClassicAccessMode)
{
}

PurrFX::CDpcmDataFileReader::~CDpcmDataFileReader()
{
	for (auto* pSample: m_aSamples)
		delete pSample;
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataFileReader::getSample(uint8_t i_nAddress, uint8_t i_nLength) const
{
	if (!m_bClassicAccessModeEnabled)
		return nullptr;

	uint16_t nKey = key(i_nAddress, i_nLength);
	std::map<uint16_t, CDpcmSample*>::const_iterator iSample = m_mSamples.find(nKey);
	if (iSample == m_mSamples.cend())
		return nullptr;
	return iSample->second;
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataFileReader::getSample() const
{
	if (m_bIsCurrentIndexSet &&
		m_nCurrentIndex < m_aSamples.size())
		return m_aSamples[m_nCurrentIndex];
	return nullptr;
}


bool PurrFX::CDpcmDataFileReader::setCurrentIndex(size_t i_nCurrentIndex)
{
	if (i_nCurrentIndex >= m_aSamples.size())
		return false;
	m_nCurrentIndex = i_nCurrentIndex;
	m_bIsCurrentIndexSet = true;
	return true;
}

size_t PurrFX::CDpcmDataFileReader::size() const
{
	return m_aSamples.size();
}

void PurrFX::CDpcmDataFileReader::load(const pathstring& i_sFileName)
{
	CDpcmSample* pSample = CDpcmFile::load(i_sFileName);
	if (pSample == nullptr)
		return;

	m_aSamples.push_back(pSample);

	if (m_bClassicAccessModeEnabled)
	{
		uint16_t nKey = key(pSample->dpcmAddress(), pSample->dpcmLength());
		m_mSamples[nKey] = pSample;
	}
}

uint16_t PurrFX::CDpcmDataFileReader::key(uint8_t i_nAddress, uint8_t i_nLength) const
{
	return i_nAddress + ( uint16_t(i_nLength) << 8 );
}
