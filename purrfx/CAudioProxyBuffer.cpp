#include "CAudioProxyBuffer.h"

PurrFX::CAudioProxyBuffer::CAudioProxyBuffer(int i_nSrcBitDepth, int i_nSrcChannels):
	m_nSrcBitDepth(i_nSrcBitDepth),
	m_nSrcChannels(i_nSrcChannels),
	m_nSrcSampleBytes( m_nSrcChannels*(m_nSrcBitDepth/8) )
{
	assert(m_nSrcBitDepth == 8 || m_nSrcBitDepth == 16);
	assert(m_nSrcChannels == 1 || m_nSrcChannels ==  2);
	assert(m_aSrcData.size() % m_nSrcSampleBytes == 0);

	reset();
}

void PurrFX::CAudioProxyBuffer::reset()
{
	// No data to process -> will request new data
	m_nSrcDataUsed = m_aSrcData.size();
}

bool PurrFX::CAudioProxyBuffer::getData(char* o_pDstData, size_t i_nDstSize, int i_nBitDepth, int i_nChannels, CAudioProxyBufferDataProvider* i_pDataProvider)
{
	assert(i_nBitDepth == 8 || i_nBitDepth == 16);
	assert(i_nChannels == 1 || i_nChannels ==  2);
	const size_t nDstSampleBytes = i_nChannels*(i_nBitDepth/8);
	assert(i_nDstSize % nDstSampleBytes == 0);

	bool bSuccess = true;
	while(i_nDstSize > 0 && bSuccess)
	{
		while(m_nSrcDataUsed < m_aSrcData.size() &&
		      i_nDstSize > 0)
		{
			// Get source sample data
			const char* pSrcData = m_aSrcData.data()+m_nSrcDataUsed;
			static_assert(sizeof(int) >= 4, "Int is too small");
			int nSrcL = int( m_nSrcBitDepth == 8 ? reinterpret_cast<const uint8_t*>(pSrcData)[0] : reinterpret_cast<const int16_t*>(pSrcData)[0] );
			int nSrcR = m_nSrcChannels == 1 ? nSrcL :
						int( m_nSrcBitDepth == 8 ? reinterpret_cast<const uint8_t*>(pSrcData)[1] : reinterpret_cast<const int16_t*>(pSrcData)[1] );
			int nSrcA = (nSrcL+nSrcR)/2;

			// Convert to destination format
			int nDstL = nSrcL;
			int nDstR = nSrcR;
			int nDstA = nSrcA;
			if (i_nBitDepth != m_nSrcBitDepth)
			{
				if (i_nBitDepth == 16)
				{
					nDstL = convert8to16(nDstL);
					nDstR = convert8to16(nDstR);
					nDstA = convert8to16(nDstA);
				}
				else if (i_nBitDepth == 8)
				{
					nDstL = convert16to8(nDstL);
					nDstR = convert16to8(nDstR);
					nDstA = convert16to8(nDstA);
				}
			}

			// Put into destination buffer
			if (i_nBitDepth == 8)
			{
				uint8_t* pDstData = reinterpret_cast<uint8_t*>(o_pDstData);
				if      (i_nChannels == 1)
					pDstData[0] = uint8_t(nDstA);
				else if (i_nChannels == 2)
				{
					pDstData[0] = uint8_t(nDstL);
					pDstData[1] = uint8_t(nDstR);
				}
			}
			else if (i_nBitDepth == 16)
			{
				int16_t* pDstData = reinterpret_cast<int16_t*>(o_pDstData);
				if      (i_nChannels == 1)
					pDstData[0] = int16_t(nDstA);
				else if (i_nChannels == 2)
				{
					pDstData[0] = int16_t(nDstL);
					pDstData[1] = int16_t(nDstR);
				}
			}

			// Move to next source/destination sample
			m_nSrcDataUsed += m_nSrcSampleBytes;

			i_nDstSize -= nDstSampleBytes;
			o_pDstData += nDstSampleBytes;
		}
			
		// Get next portion of source data if it is necessary
		if (m_nSrcDataUsed == m_aSrcData.size())
		{
			m_nSrcDataUsed = 0;
			bSuccess = i_pDataProvider->getData(m_aSrcData.data(), m_aSrcData.size());
		}
	}

	return bSuccess;
}

int PurrFX::CAudioProxyBuffer::convert8to16(int v) { return v*256 - _I16_MAX; }
int PurrFX::CAudioProxyBuffer::convert16to8(int v) { return v/256 + _I8_MAX; }
