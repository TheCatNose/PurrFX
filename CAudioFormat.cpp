#include "CAudioFormat.h"

PurrFX::CAudioFormat::CAudioFormat():
	m_nSampleRate(44100),
	m_bStereo(true),
	m_nBitDepth(16)
{
}

PurrFX::CAudioFormat::CAudioFormat(int i_nSampleRate, bool i_bStereo, int i_nBitDepth):
	m_nSampleRate(i_nSampleRate),
	m_bStereo(i_bStereo),
	m_nBitDepth(i_nBitDepth)
{
	// Check format and apply fixes

	if (m_nSampleRate !=  8000 &&
		m_nSampleRate != 11025 &&
		m_nSampleRate != 22050 &&
		m_nSampleRate != 32000 &&
		m_nSampleRate != 44100 &&
		m_nSampleRate != 48000 )
		m_nSampleRate  = 41000;

	if (m_nBitDepth != 8 &&
		m_nBitDepth != 16)
		m_nBitDepth  = 16;
}

int PurrFX::CAudioFormat::sampleRate() const { return m_nSampleRate; }
int PurrFX::CAudioFormat::channels()   const { return m_bStereo?2:1; }
int PurrFX::CAudioFormat::bitDepth()   const { return m_nBitDepth; }

int PurrFX::CAudioFormat::bytesPerSample() const
{
	return bitDepth()/8;
}
