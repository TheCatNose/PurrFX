#include "CNes.h"

PurrFX::CNes::~CNes()
{
}

bool PurrFX::CNes::setSoundOptions(int i_nSampleRate)
{
	if (i_nSampleRate !=  8000 &&
		i_nSampleRate != 11025 &&
		i_nSampleRate != 22050 &&
		i_nSampleRate != 32000 &&
		i_nSampleRate != 44100 &&
		i_nSampleRate != 48000 )
		return false;

	m_nSoundSampleRate = i_nSampleRate;
	return true;
}

int PurrFX::CNes::soundSampleRate()
{
	return m_nSoundSampleRate;
}

void PurrFX::CNes::setLogDataConsumer(CNesLogDataConsumer* i_pConsumer)
{
	m_pLogDataConsumer = i_pConsumer;
}

void PurrFX::CNes::setLogItemTypeEnabled(ENesLogItemType i_eType)
{
	size_t nBit = size_t(i_eType);
	assert(nBit < m_aLogItemTypesDisabled.size());
	m_aLogItemTypesDisabled.reset(nBit);
}

void PurrFX::CNes::setLogItemTypeDisabled(ENesLogItemType i_eType)
{
	size_t nBit = size_t(i_eType);
	assert(nBit < m_aLogItemTypesDisabled.size());
	m_aLogItemTypesDisabled.set(nBit);
}

bool PurrFX::CNes::logEnabled() const
{
	return (m_pLogDataConsumer != nullptr);
}

void PurrFX::CNes::logAddItem(const CNesLogItem& i_rItem)
{
	if (m_pLogDataConsumer == nullptr)
		return;

	size_t nBit = size_t( i_rItem.type() );
	assert(nBit < m_aLogItemTypesDisabled.size());
	if (m_aLogItemTypesDisabled.test(nBit))
		return;

	m_pLogDataConsumer->onNewItem(&i_rItem);
}
