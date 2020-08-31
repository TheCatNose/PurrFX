#include "CFrameDataFileReader.h"

PurrFX::CFrameDataFileReader::CFrameDataFileReader(const pathchar_t* i_sFileName)
{
	CFile oFile(i_sFileName, CFile::Read);

	if (oFile.isOpened()) do
	{
		const size_t nFileSize = oFile.size();
		size_t nBytesRead = 0;

		// Header

		char sFormat[2];
		nBytesRead = oFile.read(sFormat, 2);
		if (nBytesRead != 2   ||
			sFormat[0] != 'F' ||
			sFormat[1] != 'D')
			break;
		
		uint8_t aHdrData[2];
		nBytesRead = oFile.read(aHdrData, 2);
		if (nBytesRead  != 2  ||
			aHdrData[0] != 1            || // Wrong version
			aHdrData[1] == 0            || // Wrong register count
			aHdrData[1] > RegisterCount )
			break;

		const size_t nHeaderSize         = 4;
		const size_t nDataSize           = nFileSize - nHeaderSize;
		const size_t nRegisterCount      = aHdrData[1];
		const size_t nWriteMarksBytes    = nRegisterCount/8 + (nRegisterCount%8 == 0 ? 0 : 1);
		const size_t nValuesBytes        = nRegisterCount;
		const size_t nFrameDataItemBytes = nWriteMarksBytes + nValuesBytes;
		const size_t nFrameDataItems     = nDataSize/nFrameDataItemBytes;

		m_pData = new CFrameData[nFrameDataItems];

		// Frame data items

		uint8_t* pWriteMarks = new uint8_t[nWriteMarksBytes];
		uint8_t* pValues     = new uint8_t[nValuesBytes];

		for (size_t nItemIndex = 0; nItemIndex < nFrameDataItems; nItemIndex++)
		{
			nBytesRead = 
				oFile.read(pWriteMarks, nWriteMarksBytes) + 
				oFile.read(pValues    , nValuesBytes    );
			if (nBytesRead != nFrameDataItemBytes)
				break;
			m_nDataItems++;

			CFrameData& rData = m_pData[nItemIndex];
			
			for (size_t nRegisterIndex = 0; nRegisterIndex < nRegisterCount; nRegisterIndex++)
			{
				ERegister eRegister = ERegister(nRegisterIndex);

				size_t nMarkByte = nRegisterIndex/8;
				size_t nMarkBit  = nRegisterIndex%8;
				bool bSet = ((pWriteMarks[nMarkByte] >> nMarkBit) & 1U) != 0;
				if (bSet)
					rData.set(eRegister, pValues[nRegisterIndex]);
			}
		}

		delete[] pWriteMarks;
		delete[] pValues;

	} while(false);
}

PurrFX::CFrameDataFileReader::~CFrameDataFileReader()
{
	if (m_pData != nullptr)
		delete[] m_pData;
}

bool PurrFX::CFrameDataFileReader::available() const
{
	return m_nDataItemCurrentIndex < m_nDataItems;
}

PurrFX::CFrameData PurrFX::CFrameDataFileReader::get() const
{
	if (!available())
		return CFrameData();
	return m_pData[m_nDataItemCurrentIndex];
}

bool PurrFX::CFrameDataFileReader::next()
{
	if (m_nDataItems == 0)
		return false;

	assert(m_nDataItemCurrentIndex < m_nDataItems);
	if (m_nDataItemCurrentIndex >= m_nDataItems-1)
		return false;
	m_nDataItemCurrentIndex++;
	return true;
}

size_t PurrFX::CFrameDataFileReader::size() const
{
	return m_nDataItems;
}

PurrFX::CFrameData PurrFX::CFrameDataFileReader::getAt(size_t i_nIndex) const
{
	assert(i_nIndex < m_nDataItems);
	return m_pData[i_nIndex];
}
