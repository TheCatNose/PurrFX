#include "CNesLogFileWriter.h"

namespace PurrFX
{
	CNesLogFileWriter::CNesLogFileWriter(const char* i_sFileName):
		m_oFile(i_sFileName, CBufferedFileWriter::MAX_BUFFER_SIZE)
	{
	}

	void CNesLogFileWriter::onNewItem(const CNesLogItem* i_pLogItem)
	{
		if (!m_oFile.isOpened())
			return;

		switch(i_pLogItem->type())
 		{
		case ENesLogItemType::CpuInstruction:
			{
				auto* pLogItem = dynamic_cast<const CNesLogItemCpuInstruction*>(i_pLogItem);
				CNesCpuInstructionInfo oInfo(pLogItem->opcode());

				char sBuffer[32];
				int nChars;

				// Address, opcode, name
				nChars = sprintf_s<32>(sBuffer,
					"$%04X: %02X (%s)",
					pLogItem->address(),
					pLogItem->opcode(),
					oInfo.name()
				);
				if (nChars > 0)
					m_oFile.write(sBuffer, nChars);

				// Argument(s) bytes
				const int nArgBytes = oInfo.argBytes();
				assert(nArgBytes >= 0 && nArgBytes <= 2);
				if (nArgBytes >= 1)
				{
					nChars = sprintf_s<32>(sBuffer, " %02X", pLogItem->argByte1());
					if (nChars > 0)
						m_oFile.write(sBuffer, nChars);
				}
				if (nArgBytes == 2)
				{
					nChars = sprintf_s<32>(sBuffer, " %02X", pLogItem->argByte2());
					if (nChars > 0)
						m_oFile.write(sBuffer, nChars);
				}

				// Newline
				m_oFile.write("\n", 1);
			}
			break;
		default:
			assert(false && "Unknown log item type");
		}
	}
}