#include "CFrameDataFileWriter.h"

PurrFX::CFrameDataFileWriter::CFrameDataFileWriter(const pathchar_t* i_sFileName):
	m_oFile(i_sFileName)
{
	if (!m_oFile.isOpened())
		return;

	// Header format:
	// "FD"           - 2 bytes string
	// Version        - 1 byte, unsigned
	// Register count - 1 byte, unsigned

	static_assert(RegisterCount <= 0xFF, "Too many registers");
		
	const uint8_t nVersion       = 1;
	const uint8_t nRegisterCount = RegisterCount;
	m_oFile.write("FD", 2);
	m_oFile.write(&nVersion, sizeof(nVersion));
	m_oFile.write(&nRegisterCount, sizeof(nRegisterCount));
}

void PurrFX::CFrameDataFileWriter::onFrameDataReady(const CFrameData& i_rFrameData)
{
	if (!m_oFile.isOpened())
		return;

	// Frame data item format:
	// Write marks     - X bytes (depends on register count, for example 2 bytes for 9 registers)
	// Register Values - Y bytes (by register count)

	// Write marks

	constexpr size_t nMarksBytes = RegisterCount/8 + (RegisterCount%8 == 0 ? 0 : 1);
	std::array<uint8_t, nMarksBytes> aMarks;
	std::fill(aMarks.begin(), aMarks.end(), 0);

	for (size_t i = 0; i < RegisterCount; i++)
	{
		ERegister eRegister = ERegister(i);
		if (i_rFrameData.isSet(eRegister))
		{
			const size_t nByte = i/8;
			const size_t nBit  = i%8;
			aMarks[nByte] |= (uint8_t(1) << nBit);
		}
	}
	
	m_oFile.write(aMarks.data(), aMarks.size());

	// Register values

	for (size_t i = 0; i < RegisterCount; i++)
	{
		ERegister eRegister = ERegister(i);
		uint8_t nValue = i_rFrameData.get(eRegister);
		m_oFile.write(&nValue, sizeof(nValue));
	}
}
