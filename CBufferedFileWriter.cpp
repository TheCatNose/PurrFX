#include "CBufferedFileWriter.h"

PurrFX::CBufferedFileWriter::CBufferedFileWriter(const pathstring& i_sFileName, size_t i_nBufferSize):
	m_oFile(i_sFileName, CFile::Write),
	m_nBufferSize(i_nBufferSize)
{
	assert(i_nBufferSize >= MIN_BUFFER_SIZE); // It must be big enough to make sense
	assert(i_nBufferSize <= MAX_BUFFER_SIZE); // And it must not be too big either

	if (!m_oFile.isOpened())
		return;

	m_pBuffer = new char[m_nBufferSize];
}

PurrFX::CBufferedFileWriter::~CBufferedFileWriter()
{
	if (m_nBufferBytesUsed > 0)
	{
		assert(m_oFile.isOpened());
		assert(m_pBuffer != nullptr);
		m_oFile.write(m_pBuffer, m_nBufferBytesUsed);
		delete[] m_pBuffer;
	}
}

bool PurrFX::CBufferedFileWriter::isOpened() const
{
	return (m_oFile.isOpened());
}

void PurrFX::CBufferedFileWriter::write(const void* i_pData, size_t i_nSize)
{
	if (!m_oFile.isOpened())
		return;
	if (i_nSize == 0) // Probably empty string
		return;

	size_t nDataOffset = 0;
	const char* pData = static_cast<const char*>(i_pData);

	while (i_nSize > 0)
	{
		assert(m_nBufferBytesUsed < m_nBufferSize);
		size_t nBufferBytesFree = m_nBufferSize - m_nBufferBytesUsed;
		size_t nBytesToAdd = (i_nSize <= nBufferBytesFree ? i_nSize : nBufferBytesFree);

		memcpy(m_pBuffer + m_nBufferBytesUsed, pData + nDataOffset, nBytesToAdd);
		nDataOffset += nBytesToAdd;
		i_nSize     -= nBytesToAdd;

		m_nBufferBytesUsed += nBytesToAdd;
		assert(m_nBufferBytesUsed <= m_nBufferSize);
		if (m_nBufferBytesUsed == m_nBufferSize)
		{
			m_oFile.write(m_pBuffer, m_nBufferSize);
			m_nBufferBytesUsed = 0;
		}
	}
}
