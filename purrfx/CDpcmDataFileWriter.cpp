#include "CDpcmDataFileWriter.h"
#include "CDpcmSample.h"
#include "DNesConsts.h"
#include "CDpcmFile.h"

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

	CDpcmFile::save(i_rSample, sPath.data(), m_eType);
}
