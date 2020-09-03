#include "CDpcmDataFileWriter.h"
#include "CDpcmSample.h"
#include "DNesConsts.h"
#include "CDpcmFile.h"

PurrFX::CDpcmDataFileWriter::CDpcmDataFileWriter(const pathchar_t* i_sOutputFolder, EDpcmFileType i_eType):
	m_sOutputFolder(i_sOutputFolder),
	m_eType(i_eType)
{
	if (m_sOutputFolder.size() == 0)
		m_sOutputFolder = PATHSTR("./");
	else
	{
		size_t     nLastCharIndex = m_sOutputFolder.size()-1;
		pathchar_t nLastChar      = m_sOutputFolder[nLastCharIndex];
		if (nLastChar != '/'  &&
			nLastChar != '\\' )
			m_sOutputFolder += '/';
	}
}

const PurrFX::pathchar_t* PurrFX::CDpcmDataFileWriter::fileExtension() const
{
	switch (m_eType)
	{
	case EDpcmFileType::Dmc: return PATHSTR("dmc");
	case EDpcmFileType::Raw: return PATHSTR("raw");
	default:
		assert(false && "Unknown DPCM file type");
		return PATHSTR("");
		break;
	}
}

void PurrFX::CDpcmDataFileWriter::onSampleReady(const CDpcmSample& i_rSample)
{
	pathchar_t sFileName[32];
#ifdef _WIN32
	swprintf_s<32>(
#else
	sprintf(
#endif
		sFileName,
		PATHSTR("%02X%02X.%s"),
		i_rSample.dpcmAddress(),
		i_rSample.dpcmLength(),
		fileExtension() );

	pathstring sPath = m_sOutputFolder + sFileName;

	CDpcmFile::save(i_rSample, sPath.data(), m_eType);
}
