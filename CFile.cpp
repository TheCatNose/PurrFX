#include "CFile.h"

PurrFX::CFile::CFile(const pathchar_t* i_sPath, EMode i_eMode)
{
#ifdef _WIN32
	const pathchar_t* sMode = (i_eMode == Read ? L"rb" : L"wb");
	_wfopen_s(&m_pFile, i_sPath, sMode);
#else
	const pathchar_t* sMode = (i_eMode == Read ?  "rb" :  "wb");
	m_pFile = fopen(i_sPath, sMode);
#endif
}

PurrFX::CFile::~CFile()
{
	if (m_pFile != nullptr)
		fclose(m_pFile);
}

size_t PurrFX::CFile::read(void* o_pBuffer, size_t i_nBytes)
{
#ifdef _WIN32
	return fread_s(o_pBuffer, i_nBytes, 1, i_nBytes, m_pFile);
#else
	return fread(o_pBuffer, 1, i_nBytes, m_pFile);
#endif
}

size_t PurrFX::CFile::write(const void* i_pBuffer, size_t i_nBytes)
{
	return fwrite(i_pBuffer, 1, i_nBytes, m_pFile);
}

bool PurrFX::CFile::isOpened() const
{
	return (m_pFile != nullptr);
}

size_t PurrFX::CFile::size() const
{
	if (!isOpened())
		return 0;

	// Save position
	auto nPosition = ftell(m_pFile);
	
	fseek(m_pFile, 0, SEEK_END);
	auto nFileSize = ftell(m_pFile);
	
	// Restore position
	fseek(m_pFile, nPosition, SEEK_SET);

	return size_t(nFileSize < 0 ? 0: nFileSize);
}

PurrFX::CFile::operator FILE* () const
{
	return m_pFile;
}
