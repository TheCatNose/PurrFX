#include "CPcmSample.h"

PurrFX::CPcmSample::CPcmSample(sample_t i_nSample)
{
	m_nSample = i_nSample;
}

PurrFX::CPcmSample::CPcmSample()
{
}

PurrFX::CPcmSample::CPcmSample(uint8_t i_nValue):
	CPcmSample(
		int8_t( 
			int32_t(i_nValue                          ) - 
			int32_t(std::numeric_limits<int8_t>::min())
		)
	)
{
}

PurrFX::CPcmSample::CPcmSample(int8_t i_nValue)
{
	m_nSample = i_nValue > 0
		? i_nValue / sample_t(  std::numeric_limits<int8_t>::max() )
		: i_nValue / sample_t( -std::numeric_limits<int8_t>::min() );
	assert(m_nSample >= -1.0L && m_nSample <= 1.0L);
}

PurrFX::CPcmSample::CPcmSample(uint16_t i_nValue):
	CPcmSample(
		int16_t( 
			int32_t(i_nValue                           ) - 
			int32_t(std::numeric_limits<int16_t>::min())
		)
	)
{
}

PurrFX::CPcmSample::CPcmSample(int16_t i_nValue)
{
	m_nSample = i_nValue > 0
		? i_nValue / sample_t(  std::numeric_limits<int16_t>::max() )
		: i_nValue / sample_t( -std::numeric_limits<int16_t>::min() );
	assert(m_nSample >= -1.0L && m_nSample <= 1.0L);
}

PurrFX::CPcmSample PurrFX::CPcmSample::toMono(const CPcmSample& i_rLeft, const CPcmSample& i_rRight)
{
	return CPcmSample( (i_rLeft.m_nSample+i_rRight.m_nSample)/2.0L );
}

uint8_t PurrFX::CPcmSample::toU8() const
{
	sample_t nSample = (m_nSample + 1.0L)/2.0L;
	assert(nSample >= 0 && nSample <= 1.0);
	sample_t nResult = nSample*std::numeric_limits<uint8_t>::max();
	assert(nResult >= std::numeric_limits<uint8_t>::min() &&
		   nResult <= std::numeric_limits<uint8_t>::max() );
	return uint8_t(nResult);
}

int8_t PurrFX::CPcmSample::toS8() const
{
	sample_t nResult = m_nSample * ( m_nSample < 0
		? -std::numeric_limits<int8_t>::min()
		:  std::numeric_limits<int8_t>::max()
		);
	assert(nResult >= std::numeric_limits<int8_t>::min() &&
		   nResult <= std::numeric_limits<int8_t>::max() );
	return int16_t(nResult);
}

uint16_t PurrFX::CPcmSample::toU16() const
{
	sample_t nSample = (m_nSample + 1.0L)/2.0L;
	assert(nSample >= 0 && nSample <= 1.0);
	sample_t nResult = nSample*std::numeric_limits<uint16_t>::max();
	assert(nResult >= std::numeric_limits<uint16_t>::min() &&
		   nResult <= std::numeric_limits<uint16_t>::max() );
	return uint16_t(nResult);
}

int16_t PurrFX::CPcmSample::toS16() const
{
	sample_t nResult = m_nSample * ( m_nSample < 0
		? -std::numeric_limits<int16_t>::min()
		:  std::numeric_limits<int16_t>::max()
		);
	assert(nResult >= std::numeric_limits<int16_t>::min() &&
		   nResult <= std::numeric_limits<int16_t>::max() );
	return int16_t(nResult);
}
