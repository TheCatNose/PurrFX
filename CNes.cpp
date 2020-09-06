#include "CNes.h"
#include "CNsfTemplate.h"

PurrFX::CNes::~CNes()
{
}

bool PurrFX::CNes::open()
{
	std::vector<uint8_t> aNsf;
	CNsfTemplate::create(aNsf);
	return open(aNsf.data(), aNsf.size());
}

void PurrFX::CNes::setAudioFormat(const CAudioFormat& i_rFormat)
{
	m_oAudioFormat = i_rFormat;
}

const PurrFX::CAudioFormat& PurrFX::CNes::audioFormat()
{
	return m_oAudioFormat;
}

bool PurrFX::CNes::render()
{
	const uint32_t nBufferSize = 1024;
	char           aBuffer[nBufferSize];

	assert(m_pAudioDataConsumer != nullptr ||
		   m_pFrameDataConsumer != nullptr );

	if (m_pAudioDataConsumer != nullptr)
		m_pAudioDataConsumer->start( m_oAudioFormat );
	
	while( (m_pAudioDataConsumer == nullptr ? true : !m_pAudioDataConsumer->finished()) &&
		   (m_pFrameDataConsumer == nullptr ? true : !m_pFrameDataConsumer->finished()) )
	{
		uint32_t nSize = nBufferSize;
		if (m_pAudioDataConsumer != nullptr)
			if (nSize > m_pAudioDataConsumer->bytesToProcess())
				nSize = m_pAudioDataConsumer->bytesToProcess();

		if (!render(aBuffer, nSize))
			return false;

		if (m_pAudioDataConsumer != nullptr)
			m_pAudioDataConsumer->processData(aBuffer, nBufferSize);
	}
	return true;
}

void PurrFX::CNes::setAudioDataConsumer(CAudioDataConsumer* i_pConsumer)
{
	m_pAudioDataConsumer = i_pConsumer;
}

bool PurrFX::CNes::usesAudioDataConsumer() const
{
	return (m_pAudioDataConsumer != nullptr);
}

void PurrFX::CNes::setLogDataConsumer(CLogDataConsumer* i_pConsumer)
{
	m_pLogDataConsumer = i_pConsumer;
}

void PurrFX::CNes::logItemTypeEnable(ELogItemType i_eType)
{
	size_t nBit = size_t(i_eType);
	assert(nBit < m_aLogItemTypesDisabled.size());
	m_aLogItemTypesDisabled.reset(nBit);
}

void PurrFX::CNes::logItemTypeDisable(ELogItemType i_eType)
{
	size_t nBit = size_t(i_eType);
	assert(nBit < m_aLogItemTypesDisabled.size());
	m_aLogItemTypesDisabled.set(nBit);
}

bool PurrFX::CNes::logEnabled() const
{
	return (m_pLogDataConsumer != nullptr);
}

void PurrFX::CNes::logAddItem(const CLogItem& i_rItem)
{
	if (m_pLogDataConsumer == nullptr)
		return;

	size_t nBit = size_t( i_rItem.type() );
	assert(nBit < m_aLogItemTypesDisabled.size());
	if (m_aLogItemTypesDisabled.test(nBit))
		return;

	m_pLogDataConsumer->onNewItem(&i_rItem);
}

void PurrFX::CNes::setFrameDataConsumer(CFrameDataConsumer* i_pConsumer)
{
	m_pFrameDataConsumer = i_pConsumer;
}

void PurrFX::CNes::setFrameDataProducer(CFrameDataProducer* i_pProducer)
{
	m_pFrameDataProducer = i_pProducer;
}

PurrFX::CFrameDataConsumer* PurrFX::CNes::frameDataConsumer() const
{
	return m_pFrameDataConsumer;
}

bool PurrFX::CNes::usesFrameDataConsumer() const
{
	return (m_pFrameDataConsumer != nullptr);
}

PurrFX::CFrameDataProducer* PurrFX::CNes::frameDataProducer() const
{
	return m_pFrameDataProducer;
}

bool PurrFX::CNes::usesFrameDataProducer() const
{
	return (m_pFrameDataProducer != nullptr);
}

void PurrFX::CNes::setDpcmDataConsumer(CDpcmDataConsumer* i_pConsumer)
{
	m_pDpcmDataConsumer = i_pConsumer;
}

void PurrFX::CNes::setDpcmDataProvider(CDpcmDataProvider* i_pProvider)
{
	m_pDpcmDataProvider = i_pProvider;
}

PurrFX::CDpcmDataConsumer* PurrFX::CNes::dpcmDataConsumer() const
{
	return m_pDpcmDataConsumer;
}

bool PurrFX::CNes::usesDpcmDataConsumer() const
{
	return (m_pDpcmDataConsumer != nullptr);
}

PurrFX::CDpcmDataProvider* PurrFX::CNes::dpcmDataProvider() const
{
	return m_pDpcmDataProvider;
}

bool PurrFX::CNes::usesDpcmDataProvider() const
{
	return (m_pDpcmDataProvider != nullptr);
}
