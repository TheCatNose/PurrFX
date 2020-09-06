#include "CDpcmDataFileReader.h"

PurrFX::CDpcmDataFileReader::CDpcmDataFileReader(bool i_bUseClassicAccessMode):
	m_oStorage(i_bUseClassicAccessMode)
{
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataFileReader::getSample(uint8_t i_nAddress, uint8_t i_nLength) const
{
	return m_oStorage.get(i_nAddress, i_nLength);
}

const PurrFX::CDpcmSample* PurrFX::CDpcmDataFileReader::getSample() const
{
	return m_oStorage.get();
}

bool PurrFX::CDpcmDataFileReader::setCurrentIndex(size_t i_nCurrentIndex)
{
	return m_oStorage.setCurrent(i_nCurrentIndex);
}

size_t PurrFX::CDpcmDataFileReader::size() const
{
	return m_oStorage.size();
}

void PurrFX::CDpcmDataFileReader::load(const pathstring& i_sFileName)
{
	CDpcmSample* pSample = CDpcmFile::load(i_sFileName);
	if (pSample != nullptr)
		m_oStorage.add(pSample);
}
