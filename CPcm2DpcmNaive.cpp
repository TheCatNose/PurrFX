#include "CPcm2DpcmNaive.h"
#include "CNesCalculations.h"

PurrFX::CPcm2DpcmNaive::CPcm2DpcmNaive(const std::vector<uint8_t>& i_rPcmData):
	CPcm2Dpcm(i_rPcmData)
{}

PurrFX::CDpcmSample* PurrFX::CPcm2DpcmNaive::convert() const
{
	std::vector<bool> aDpcmBits;
	aDpcmBits.reserve( pcmSize() );

	bool bIncreaseIfNotChanged = false;
	uint8_t nSignal = std::numeric_limits<uint8_t>::max()/2;
	for (size_t i = 0; i < pcmSize(); i++)
	{
		const uint8_t nPcmByte = pcmByte(i);
		if (nPcmByte == nSignal)
		{
			aDpcmBits.push_back(bIncreaseIfNotChanged);
			bIncreaseIfNotChanged = !bIncreaseIfNotChanged;
		}
		else
			aDpcmBits.push_back(nPcmByte > nSignal);
		nSignal = nPcmByte;
	}

	CDpcmSample* pSample = new CDpcmSample(0, CNesCalculations::dpcmSampleLengthPack(dpcmSize()));
	assert(pSample->size() == dpcmSize());

	uint8_t nDpcmByte = 0;
	for (size_t i = 0; i < aDpcmBits.size(); i++)
	{
		size_t nBit = i%8;
		if (aDpcmBits[i])
			nDpcmByte |= (uint8_t(1) << nBit);
		if (nBit == 7)
		{
			pSample->set(i/8, nDpcmByte);
			nDpcmByte = 0;
		}
	}

	return pSample;
}
