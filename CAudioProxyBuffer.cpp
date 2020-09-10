#include "CAudioProxyBuffer.h"
#include "CPcmSample.h"

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

	bool bSameFormat =
		i_nBitDepth == m_nSrcBitDepth &&
		i_nChannels == m_nSrcChannels;
	const bool bFromMono = (m_nSrcChannels == 1);
	const bool bToMono   = (i_nChannels    == 1);

	bool bSuccess = true;
	while(i_nDstSize > 0 && bSuccess)
	{
		if (bSameFormat)
		{
			size_t nSize = std::min<size_t>(m_aSrcData.size(), i_nDstSize);
			memcpy(o_pDstData, m_aSrcData.data(), nSize);
			i_nDstSize -= nSize;
			o_pDstData += nSize;
			reset();
		}

		while(m_nSrcDataUsed < m_aSrcData.size() &&
		      i_nDstSize > 0)
		{
			const char* pSrcData = m_aSrcData.data()+m_nSrcDataUsed;

			// Perform conversion

			CPcmSample oSrcL;
			CPcmSample oSrcR;

			if      (m_nSrcBitDepth == 8)
			{
				const uint8_t* pData = reinterpret_cast<const uint8_t*>(pSrcData);
				oSrcL = CPcmSample(             pData[0]            );
				oSrcR = CPcmSample( bFromMono ? pData[0] : pData[1] );
			}
			else if (m_nSrcBitDepth == 16)
			{
				const int16_t* pData = reinterpret_cast<const int16_t*>(pSrcData);
				oSrcL = CPcmSample(             pData[0]            );
				oSrcR = CPcmSample( bFromMono ? pData[0] : pData[1] );
			}

			if      (i_nBitDepth == 8)
			{
				uint8_t* pDstData = reinterpret_cast<uint8_t*>(o_pDstData);
				if (bToMono) pDstData[0] = CPcmSample::toMono(oSrcL, oSrcR).toU8();
				else       { pDstData[0] = oSrcL.toU8(); pDstData[1] = oSrcR.toU8(); }
			}
			else if (i_nBitDepth == 16)
			{
				int16_t* pDstData = reinterpret_cast<int16_t*>(o_pDstData);
				if (bToMono) pDstData[0] = CPcmSample::toMono(oSrcL, oSrcR).toS16();
				else       { pDstData[0] = oSrcL.toS16(); pDstData[1] = oSrcR.toS16(); }
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
