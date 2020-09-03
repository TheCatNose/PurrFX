#include "CAudioDataConsumerWavWriter.h"

PurrFX::CAudioDataConsumerWavWriter::CAudioDataConsumerWavWriter(const pathchar_t* i_sFileName, uint32_t i_nDuration):
	CAudioDataConsumer(i_nDuration),
	m_oFile(i_sFileName)
{
	if (!m_oFile.isOpened())
		return;
}

void PurrFX::CAudioDataConsumerWavWriter::onStart(const CAudioFormat& i_rAudioFormat, uint32_t i_nBytesToProcess)
{
	if (!m_oFile.isOpened())
		return;
	
	uint32_t nDataSize = i_nBytesToProcess;

	// WAV header

	const int nHdrSize = 44;
	m_oFile.write("RIFF", 4);
	const uint32_t nFileSize = nDataSize + nHdrSize;
	m_oFile.write(&nFileSize, sizeof(nFileSize));
	m_oFile.write("WAVE", 4);
	m_oFile.write("fmt ", 4);
	const uint32_t nFmtChunkSize = 16;
	m_oFile.write(&nFmtChunkSize, sizeof(nFmtChunkSize));
	const uint16_t nFormat = 1; // PCM
	m_oFile.write(&nFormat, sizeof(nFormat));
	uint16_t nChannels = i_rAudioFormat.channels();
	m_oFile.write(&nChannels, sizeof(nChannels));
	uint32_t nSampleRate = i_rAudioFormat.sampleRate();
	m_oFile.write(&nSampleRate, sizeof(nSampleRate));
	uint16_t nBitsPerSample = i_rAudioFormat.bitDepth();
	uint32_t nBitRate = (nSampleRate * nBitsPerSample * nChannels) / 8;
	m_oFile.write(&nBitRate, sizeof(nBitRate));
	uint16_t nBytesPerSample = (nBitsPerSample * nChannels) / 8;
	m_oFile.write(&nBytesPerSample, sizeof(nBytesPerSample));
	m_oFile.write(&nBitsPerSample, sizeof(nBitsPerSample));
	m_oFile.write("data", 4);
	m_oFile.write(&nDataSize, sizeof(nDataSize));
}

void PurrFX::CAudioDataConsumerWavWriter::onData(const char* i_pData, uint32_t i_nSize)
{
	m_oFile.write(i_pData, i_nSize);
}
