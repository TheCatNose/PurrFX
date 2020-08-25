#include "CNes.h"

PurrFX::CNes::~CNes()
{
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

	assert(m_pAudioDataConsumer != nullptr);
	m_pAudioDataConsumer->start( m_oAudioFormat );
	
	while(!m_pAudioDataConsumer->finished())
	{
		uint32_t nSize = nBufferSize;
		if (nSize > m_pAudioDataConsumer->bytesToProcess())
			nSize = m_pAudioDataConsumer->bytesToProcess();

		if (!render(aBuffer, nSize))
			return false;
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
