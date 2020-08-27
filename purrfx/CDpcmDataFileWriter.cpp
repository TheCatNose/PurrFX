#include "CDpcmDataFileWriter.h"
#include "CDpcmSample.h"
#include "DNesConsts.h"
#include "CBufferedFileWriter.h"

PurrFX::CDpcmDataFileWriter::CDpcmDataFileWriter(const char* i_sOutputFolder):
	m_sOutputFolder(i_sOutputFolder)
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

void PurrFX::CDpcmDataFileWriter::onSampleReady(const CDpcmSample& i_rSample)
{
	char sFileName[32];
	sprintf_s<32>(sFileName, "%04X %04X.dmc",
		i_rSample.dpcmAddress(),
		i_rSample.dpcmLength() );

	std::string sPath = m_sOutputFolder + sFileName;
	CBufferedFileWriter oFile( sPath.data() );
	if (!oFile.isOpened())
		return;

	// Header format:
	// "DMC"          - 3 bytes string
	// Version        - 1 byte, unsigned
	// Sample address - 1 byte, unsigned

	oFile.write("DMC", 3);
	uint8_t nVersion = 1;
	uint8_t nAddress = i_rSample.dpcmAddress();
	oFile.write(&nVersion, 1);
	oFile.write(&nAddress, 1);

	// Data

	const size_t nDataSize = i_rSample.size();
	assert(nDataSize >= NesConsts::dpcmSampleLengthMin &&
		   nDataSize <= NesConsts::dpcmSampleLengthMax);
	oFile.write( i_rSample.data(), i_rSample.size() );
}
