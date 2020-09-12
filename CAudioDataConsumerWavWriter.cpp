#include "CAudioDataConsumerWavWriter.h"
#include "CWavHeader.h"

PurrFX::CAudioDataConsumerWavWriter::CAudioDataConsumerWavWriter(const pathstring& i_sFileName, uint32_t i_nDuration):
	CAudioDataConsumer(i_nDuration),
	m_oFile(i_sFileName)
{
	assert(i_nDuration != CAudioDataConsumer::InfiniteDuration);

	if (!m_oFile.isOpened())
		return;
}

void PurrFX::CAudioDataConsumerWavWriter::onStart(const CAudioFormat& i_rAudioFormat, uint32_t i_nBytesToProcess)
{
	if (!m_oFile.isOpened())
		return;
	
	CWavHeader oHeader(i_nBytesToProcess, i_rAudioFormat);
	assert(oHeader.isValid());
	CWavHeader::DataArray aData;
	oHeader.get(aData);
	m_oFile.write(aData.data(), aData.size());
}

void PurrFX::CAudioDataConsumerWavWriter::onData(const char* i_pData, uint32_t i_nSize)
{
	m_oFile.write(i_pData, i_nSize);
}
