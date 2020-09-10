#include "CAudioFormat.h"

PurrFX::CAudioFormat::CAudioFormat():
	m_nSampleRate(0),
	m_bStereo(false),
	m_nBitDepth(0)
{
}

PurrFX::CAudioFormat::CAudioFormat(int i_nSampleRate, bool i_bStereo, int i_nBitDepth):
	m_nSampleRate(i_nSampleRate),
	m_bStereo(i_bStereo),
	m_nBitDepth(i_nBitDepth)
{
}

PurrFX::CAudioFormat PurrFX::CAudioFormat::defaultFormat()
{
	return CAudioFormat{44100,true,16};
}

bool PurrFX::CAudioFormat::isValid() const
{
	if (m_nSampleRate !=  8000 &&
		m_nSampleRate != 11025 &&
		m_nSampleRate != 22050 &&
		m_nSampleRate != 32000 &&
		m_nSampleRate != 44100 &&
		m_nSampleRate != 48000 )
		return false;

	if (m_nBitDepth != 8 &&
		m_nBitDepth != 16)
		return false;

	return true;
}

int PurrFX::CAudioFormat::sampleRate() const { return m_nSampleRate; }
int PurrFX::CAudioFormat::channels()   const { return m_bStereo?2:1; }
int PurrFX::CAudioFormat::bitDepth()   const { return m_nBitDepth; }

int PurrFX::CAudioFormat::bytesPerSample() const
{
	return bitDepth()/8;
}
