#include "CDpcmDataFileWriter.h"
#include "CDpcmSample.h"
#include "DNesConsts.h"
#include "CBufferedFileWriter.h"

PurrFX::CDpcmDataFileWriter::CDpcmDataFileWriter(const char* i_sOutputFolder, EDpcmFileType i_eType):
	m_sOutputFolder(i_sOutputFolder),
	m_eType(i_eType)
{
	if (m_sOutputFolder.size() == 0)
		m_sOutputFolder = "./";
	else
	{
		size_t nLastCharIndex = m_sOutputFolder.size()-1;
		char   nLastChar      = m_sOutputFolder[nLastCharIndex];
		if (nLastChar != '/'  &&
			nLastChar != '\\' )
			m_sOutputFolder += '/';
	}
}

const char* PurrFX::CDpcmDataFileWriter::fileExtension() const
{
	switch (m_eType)
	{
	case EDpcmFileType::Dmc: return "dmc";
	case EDpcmFileType::Raw: return "raw";
	default:
		assert(false && "Unknown DPCM file type");
		return "";
		break;
	}
}

void PurrFX::CDpcmDataFileWriter::onSampleReady(const CDpcmSample& i_rSample)
{
	char sFileName[32];
	sprintf_s<32>(sFileName, "%02X%02X.%s",
		i_rSample.dpcmAddress(),
		i_rSample.dpcmLength(),
		fileExtension() );

	std::string sPath = m_sOutputFolder + sFileName;
	CBufferedFileWriter oFile( sPath.data() );
	if (!oFile.isOpened())
		return;

	switch (m_eType)
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
}

void PurrFX::CDpcmDataFileWriter::saveAsDmc(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample)
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

void PurrFX::CDpcmDataFileWriter::saveAsRaw(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample)
{
	// No header, just array of 8bit signed audio samples

	int8_t nSample = 0;
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
			i_rFile.write(&nSample, 1);
		}
	}
}
