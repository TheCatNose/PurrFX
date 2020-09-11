#include "CDpcmFile.h"
#include "CNesCalculations.h"
#include "DNesConsts.h"
#include "CBufferedFileWriter.h"
#include "CPcm2DpcmNaive.h"

PurrFX::CDpcmSample* PurrFX::CDpcmFile::load(const pathstring& i_sFileName)
{
	CFile oFile(i_sFileName, CFile::Read);
	if (!oFile.isOpened())
		return nullptr;

	fseek(oFile, 0, SEEK_END);
	const size_t nFileSize = ftell(oFile);
	fseek(oFile, 0, SEEK_SET);
	
	CDpcmSample* pSample = nullptr;
	if (nFileSize > 0)
	{
		char sFmt[4] = {0,0,0,0};
		oFile.read(sFmt, 3);
		fseek(oFile, 0, SEEK_SET);
		
		if (strcmp(sFmt, "DMC") == 0)
			return loadDmc(oFile, nFileSize);
		else
			return loadRaw(oFile, nFileSize);
	}
	return pSample;
}

bool PurrFX::CDpcmFile::save(const CDpcmSample& i_rSample, const pathchar_t* i_sFileName, EDpcmFileType i_eType)
{
	
	CBufferedFileWriter oFile(i_sFileName);
	if (!oFile.isOpened())
		return false;

	switch (i_eType)
	{
	case EDpcmFileType::Dmc:
		saveAsDmc(oFile, i_rSample);
		break;
	case EDpcmFileType::Raw:
		saveAsRaw(oFile, i_rSample);
		break;
	default:
		assert(false && "Unknown DPCM file type");
	}
	return true;
}

PurrFX::CDpcmSample* PurrFX::CDpcmFile::loadDmc(CFile& i_rFile, size_t i_nFileSize)
{
	const size_t nMinFileSize = 5; // For DMC, version and packed address
	if (i_nFileSize < nMinFileSize)
		return nullptr;

	fseek(i_rFile, 3, SEEK_SET); // Skip 'DMC'
	size_t nBytesRead = 0;

	uint8_t nVersion = 0;
	nBytesRead = i_rFile.read(&nVersion, 1);
	if (nBytesRead != 1)
		return nullptr;
	if (nVersion != 1)
		return nullptr;

	uint8_t nAddress = 0;
	nBytesRead = i_rFile.read(&nAddress, 1);
	if (nBytesRead != 1)
		return nullptr;

	const size_t nDataSize_ = i_nFileSize-nMinFileSize;
	if (!CNesCalculations::isDpcmSampleLengthCorrect(nDataSize_))
		return nullptr;
	assert(nDataSize_ <= UINT16_MAX);
	uint16_t nDataSize = uint16_t(nDataSize_);

	std::vector<uint8_t> aData(nDataSize);
	nBytesRead = i_rFile.read(aData.data(), nDataSize);
	if (nBytesRead != nDataSize)
		return nullptr;

	CDpcmSample* pSample = new CDpcmSample(nAddress, CNesCalculations::dpcmSampleLengthPack(nDataSize));
	assert(pSample->size() == nDataSize);
	pSample->set(aData.data());
	return pSample;
}

PurrFX::CDpcmSample* PurrFX::CDpcmFile::loadRaw(CFile& i_rFile, size_t i_nFileSize)
{
	const size_t nDpcmSize = i_nFileSize/8;
	if (nDpcmSize < NesConsts::dpcmSampleLengthMin)
		return nullptr;
	
	const uint16_t nDpcmDataSize = CNesCalculations::closestSmallerDpcmDataLength(nDpcmSize);
	assert(nDpcmDataSize >= NesConsts::dpcmSampleLengthMin);
	assert(nDpcmDataSize <= NesConsts::dpcmSampleLengthMax);

	const uint16_t nPcmDataSize = nDpcmDataSize*8;
	assert(nPcmDataSize <= i_nFileSize);

	std::vector<uint8_t> aPcmData(nPcmDataSize);
	size_t nBytesRead = i_rFile.read(aPcmData.data(), nPcmDataSize);
	if (nBytesRead != nPcmDataSize)
		return nullptr;

	CPcm2DpcmNaive oConv(aPcmData);
	CPcm2Dpcm* pConv = &oConv;
	return pConv->convert();
}

void PurrFX::CDpcmFile::saveAsDmc(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample)
{
	// Header format:
	// "DMC"          - 3 bytes string
	// Version        - 1 byte, unsigned
	// Sample address - 1 byte, unsigned

	i_rFile.write("DMC", 3);
	uint8_t nVersion = 1;
	uint8_t nAddress = i_rSample.dpcmAddress();
	i_rFile.write(&nVersion, 1);
	i_rFile.write(&nAddress, 1);

	// Data

	const size_t nDataSize = i_rSample.size();
	assert(nDataSize >= NesConsts::dpcmSampleLengthMin &&
		   nDataSize <= NesConsts::dpcmSampleLengthMax);
	i_rFile.write( i_rSample.data(), i_rSample.size() );
}

void PurrFX::CDpcmFile::saveAsRaw(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample)
{
	// No header, just array of 8bit unsigned audio samples

	int nSample = std::numeric_limits<uint8_t>::max()/2;
	for (size_t i = 0; i < i_rSample.size(); i++)
	{
		uint8_t nSrcByte = i_rSample.data()[i];
		for (int nBit = 0; nBit < 8; nBit++)
		{
			bool bBitSet = (nSrcByte & (1<<nBit)) != 0;
			if (bBitSet)
				nSample++;
			else
				nSample--;

			int nLimited = nSample;
			if (nLimited < std::numeric_limits<uint8_t>::min())
				nLimited = std::numeric_limits<uint8_t>::min();
			if (nLimited > std::numeric_limits<uint8_t>::max())
				nLimited = std::numeric_limits<uint8_t>::max();
			
			uint8_t nSample = uint8_t(nLimited);
			i_rFile.write(&nSample, 1);
		}
	}
}
