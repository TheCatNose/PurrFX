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

PurrFX::CNesLogDataConsumer* PurrFX::CNes::logDataConsumer() const
{
	return m_pLogDataConsumer;
}
