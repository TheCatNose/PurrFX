#include "CDpcmFile.h"
#include "CNesCalculations.h"
#include "DNesConsts.h"

PurrFX::CDpcmSample* PurrFX::CDpcmFile::load(const char* i_sFileName)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, i_sFileName, "rb");
	if (pFile == nullptr)
		return nullptr;

	fseek(pFile, 0, SEEK_END);
	const size_t nFileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	
	CDpcmSample* pSample = nullptr;
	if (nFileSize > 0)
	{
		char sFmt[4] = {0,0,0,0};
		fread_s(sFmt, 3, 1, 3, pFile);
		fseek(pFile, 0, SEEK_SET);
		
		if (strcmp(sFmt, "DMC") == 0)
			return loadDmc(pFile, nFileSize);
		else
			return loadRaw(pFile, nFileSize);
	}
	return pSample;
}

PurrFX::CDpcmSample* PurrFX::CDpcmFile::loadDmc(FILE* i_pFile, size_t i_nFileSize)
{
	const size_t nMinFileSize = 5; // For DMC, version and packed address
	if (i_nFileSize < nMinFileSize)
		return nullptr;

	fseek(i_pFile, 3, SEEK_SET); // Skip 'DMC'
	size_t nBytesRead = 0;

	uint8_t nVersion = 0;
	nBytesRead = fread_s(&nVersion, 1, 1, 1, i_pFile);
	if (nBytesRead != 1)
		return nullptr;
	if (nVersion != 1)
		return nullptr;

	uint8_t nAddress = 0;
	nBytesRead = fread_s(&nAddress, 1, 1, 1, i_pFile);
	if (nBytesRead != 1)
		return nullptr;

	const size_t nDataSize_ = i_nFileSize-nMinFileSize;
	if (!CNesCalculations::isDpcmSampleLengthCorrect(nDataSize_))
		return nullptr;
	assert(nDataSize_ <= UINT16_MAX);
	uint16_t nDataSize = uint16_t(nDataSize_);

	std::vector<uint8_t> aData(nDataSize);
	nBytesRead = fread_s(aData.data(), nDataSize, 1, nDataSize, i_pFile);
	if (nBytesRead != nDataSize)
		return nullptr;

	CDpcmSample* pSample = new CDpcmSample(nAddress, CNesCalculations::dpcmSampleLengthPack(nDataSize));
	assert(pSample->size() == nDataSize);
	pSample->set(aData.data());
	return pSample;
}

PurrFX::CDpcmSample* PurrFX::CDpcmFile::loadRaw(FILE* i_pFile, size_t i_nFileSize)
{
	const size_t nDpcmSize = i_nFileSize/8;
	if (nDpcmSize < NesConsts::dpcmSampleLengthMin)
		return nullptr;
	
	const uint16_t nDpcmDataSize = CNesCalculations::closestSmallerDpcmDataLength(nDpcmSize);
	assert(nDpcmDataSize >= NesConsts::dpcmSampleLengthMin);
	assert(nDpcmDataSize <= NesConsts::dpcmSampleLengthMax);

	const uint16_t nPcmDataSize = nDpcmDataSize*8;
	assert(nPcmDataSize <= i_nFileSize);

	std::vector<int8_t> aPcmData(nPcmDataSize);
	size_t nBytesRead = fread_s(aPcmData.data(), nPcmDataSize, 1, nPcmDataSize, i_pFile);
	if (nBytesRead != nPcmDataSize)
		return nullptr;

	std::vector<bool> aDpcmBits;
	aDpcmBits.reserve(nPcmDataSize);

	// This is very naive approach.
	// Proper implementation should take into account nonstandard signal level changes.
	// (possible signal level changes for 1bit DPCM are +1 and -1)
	bool bIncreaseIfNotChanged = false;
	int8_t nSignal = 0;
	for (size_t i = 0; i < aPcmData.size(); i++)
	{
		if (aPcmData[i] == nSignal)
		{
			aDpcmBits.push_back(bIncreaseIfNotChanged);
			bIncreaseIfNotChanged = !bIncreaseIfNotChanged;
		}
		else
			aDpcmBits.push_back( aPcmData[i] > nSignal );
		nSignal = aPcmData[i];
	}

	CDpcmSample* pSample = new CDpcmSample(0, CNesCalculations::dpcmSampleLengthPack(nDpcmDataSize));
	assert(pSample->size() == nDpcmDataSize);

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
