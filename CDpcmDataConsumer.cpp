#include "CDpcmDataConsumer.h"
#include "CDpcmSample.h"

PurrFX::CDpcmDataConsumer::~CDpcmDataConsumer()
{
	for (CDpcmSample* pSample: m_lData)
		delete pSample;
}

void PurrFX::CDpcmDataConsumer::start(uint8_t i_nAddress, uint8_t i_nLength)
{
	assert(!sampleStarted());
	assert(m_nCurrentSampleBytesSet == 0);
	
	for (CDpcmSample* pSample: m_lData)
	{
		// Don't recreate the same sample
		if (pSample->dpcmAddress() == i_nAddress &&
			pSample->dpcmLength()  == i_nLength  )
			return;
	}
	m_lData.push_back( new CDpcmSample(i_nAddress, i_nLength) );
	m_pCurrentSample = m_lData.back();
}

void PurrFX::CDpcmDataConsumer::addByte(uint8_t i_nValue)
{
	if (!sampleStarted())
		return;

	bool bSet = m_pCurrentSample->set(m_nCurrentSampleBytesSet++, i_nValue);
	assert(bSet);
}

void PurrFX::CDpcmDataConsumer::end()
{
	if (!sampleStarted())
		return;

	assert(m_pCurrentSample->size() == m_nCurrentSampleBytesSet);
	onSampleReady(*m_pCurrentSample);

	m_pCurrentSample = nullptr;
	m_nCurrentSampleBytesSet = 0;
}

bool PurrFX::CDpcmDataConsumer::sampleStarted() const
{
	return m_pCurrentSample != nullptr;
}
