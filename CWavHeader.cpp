#include "CWavHeader.h"

PurrFX::CWavHeader::CWavHeader(uint32_t i_nDataSize, const CAudioFormat& i_rFormat)
{
	memcpy(m_oData.sRiff, ITEM_RIFF, strlen(ITEM_RIFF));
	m_oData.nFileSize       = i_nDataSize + HeaderSize - 8;
	memcpy(m_oData.sWave, ITEM_WAVE, strlen(ITEM_WAVE));
	memcpy(m_oData.sFmt , ITEM_FMT , strlen(ITEM_FMT));
	m_oData.nFmtChunkSize   = FMT_CHUNK_SIZE;
	m_oData.nFormat         = PCM;
	m_oData.nChannels       = uint16_t( i_rFormat.channels() );
	m_oData.nSampleRate     = uint32_t( i_rFormat.sampleRate() );
	m_oData.nBitsPerSample  = uint16_t( i_rFormat.bitDepth() );
	m_oData.nByteRate       = byteRate();
	m_oData.nBytesPerSample = bytesPerSample();
	memcpy(m_oData.sData, ITEM_DATA, strlen(ITEM_DATA));
	m_oData.nDataSize       = i_nDataSize;
}

PurrFX::CWavHeader::CWavHeader(const uint8_t* i_pData)
{
	size_t nOffset = 0;

	auto fLoadStr = [i_pData, &nOffset](char* o_pDst, size_t i_nLength) {
		const char* pSrc = reinterpret_cast<const char*>(i_pData+nOffset);
		for (size_t i = 0; i < i_nLength; i++)
			o_pDst[i] = pSrc[i];
		nOffset += i_nLength;
	};
	
	auto fLoad16 = [i_pData, &nOffset]() {
		uint16_t nValue = *( reinterpret_cast<const uint16_t*>(i_pData+nOffset) );
		nOffset += sizeof(nValue);
		return nValue;
	};

	auto fLoad32 = [i_pData, &nOffset]() {
		uint32_t nValue = *( reinterpret_cast<const uint32_t*>(i_pData+nOffset) );
		nOffset += sizeof(nValue);
		return nValue;
	};

	fLoadStr(m_oData.sRiff  , sizeof(m_oData.sRiff));
	m_oData.nFileSize       = fLoad32();
	fLoadStr(m_oData.sWave  , sizeof(m_oData.sWave));
	fLoadStr(m_oData.sFmt   , sizeof(m_oData.sFmt));
	m_oData.nFmtChunkSize   = fLoad32();
	m_oData.nFormat         = fLoad16();
	m_oData.nChannels       = fLoad16();
	m_oData.nSampleRate     = fLoad32();
	m_oData.nByteRate       = fLoad32();
	m_oData.nBytesPerSample = fLoad16();
	m_oData.nBitsPerSample  = fLoad16();
	fLoadStr(m_oData.sData  ,  sizeof(m_oData.sData));
	m_oData.nDataSize       = fLoad32();

	assert(nOffset == HeaderSize);
}

size_t PurrFX::CWavHeader::size() const
{
	return HeaderSize;
}

bool PurrFX::CWavHeader::isValid() const
{
	return !(
		( strncmp(m_oData.sRiff, ITEM_RIFF, 4) != 0                                  ) ||
		( m_oData.nFileSize                    != HeaderSize + m_oData.nDataSize - 8 ) ||
		( strncmp(m_oData.sWave, ITEM_WAVE, 4) != 0                                  ) ||
		( strncmp(m_oData.sFmt , ITEM_FMT , 4) != 0                                  ) ||
		( m_oData.nFmtChunkSize                != FMT_CHUNK_SIZE                     ) ||
		( m_oData.nFormat                      != PCM                                ) ||
		( m_oData.nChannels                    != 1 &&
		  m_oData.nChannels                    != 2                                  ) ||
		( m_oData.nSampleRate                   < 8000                               ) ||
		( m_oData.nByteRate                    != byteRate()                         ) ||
		( m_oData.nBytesPerSample              != bytesPerSample()                   ) ||
		( m_oData.nBitsPerSample               != 8  &&
		  m_oData.nBitsPerSample               != 16                                 ) ||
		( strncmp(m_oData.sData, ITEM_DATA, 4) != 0                                  ) ||
		( m_oData.nDataSize % bytesPerSample() != 0                                  ) );
}

size_t PurrFX::CWavHeader::dataSize() const
{
	return m_oData.nDataSize;
}

PurrFX::CAudioFormat PurrFX::CWavHeader::audioFormat() const
{
	CAudioFormat oFormat(
		int(m_oData.nSampleRate),
		m_oData.nChannels == 2,
		m_oData.nBitsPerSample);

	if (oFormat.sampleRate() != int(m_oData.nSampleRate) ||
		oFormat.channels()   != m_oData.nChannels        ||
		oFormat.bitDepth()   != m_oData.nBitsPerSample   )
		return CAudioFormat();
	return oFormat;
}

void PurrFX::CWavHeader::get(DataArray& o_rData) const
{
	size_t nOffset = 0;

	auto fSaveStr = [&o_rData, &nOffset](const char* i_pString) {
		const size_t nLength = 4;
		for (size_t i = 0; i < nLength; i++)
			o_rData[nOffset+i] = i_pString[i];
		nOffset += nLength;
	};

	auto fSave32 = [&o_rData, &nOffset](uint32_t i_nValue) {
		const size_t nLength = sizeof(i_nValue);
		for (size_t i = 0; i < nLength; i++)
			o_rData[nOffset+i] = reinterpret_cast<const uint8_t*>(&i_nValue)[i];
		nOffset += nLength;
	};

	auto fSave16 = [&o_rData, &nOffset](uint16_t i_nValue) {
		const size_t nLength = sizeof(i_nValue);
		for (size_t i = 0; i < nLength; i++)
			o_rData[nOffset+i] = reinterpret_cast<const uint8_t*>(&i_nValue)[i];
		nOffset += nLength;
	};

	fSaveStr( m_oData.sRiff );
	fSave32 ( m_oData.nFileSize );
	fSaveStr( m_oData.sWave );
	fSaveStr( m_oData.sFmt );
	fSave32 ( m_oData.nFmtChunkSize );
	fSave16 ( m_oData.nFormat );
	fSave16 ( m_oData.nChannels );
	fSave32 ( m_oData.nSampleRate );
	fSave32 ( m_oData.nByteRate );
	fSave16 ( m_oData.nBytesPerSample );
	fSave16 ( m_oData.nBitsPerSample );
	fSaveStr( m_oData.sData );
	fSave32 ( m_oData.nDataSize );

	assert(nOffset == HeaderSize);
}

uint32_t PurrFX::CWavHeader::byteRate() const       { return (m_oData.nBitsPerSample * m_oData.nChannels * m_oData.nSampleRate) / 8; }
uint32_t PurrFX::CWavHeader::bytesPerSample() const { return (m_oData.nBitsPerSample * m_oData.nChannels                      ) / 8; }
