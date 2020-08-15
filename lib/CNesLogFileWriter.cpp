#include "CNesLogFileWriter.h"

namespace PurrFX
{
	CNesLogFileWriter::CNesLogFileWriter(const char* i_sFileName)
	{
		fopen_s(&m_pFile, i_sFileName, "wb");
	}

	CNesLogFileWriter::~CNesLogFileWriter()
	{
		if (m_pFile != nullptr)
			fclose(m_pFile);
	}

	void CNesLogFileWriter::onNewItem(const CNesLogItem* i_pLogItem)
	{
		if (m_pFile == nullptr)
			return;

		switch(i_pLogItem->type())
 		{
		case ENesLogItemType::CpuInstruction:
			{
				auto* pLogItem = dynamic_cast<const CNesLogItemCpuInstruction*>(i_pLogItem);
				CNesCpuInstructionInfo oInfo(pLogItem->opcode());

				std::string sLine;
				sLine.reserve(32);

				// Address, opcode, name
				char sBuffer[32];
				sprintf_s<32>(sBuffer,
					"$%04X: %02X (%s)",
					pLogItem->address(),
					pLogItem->opcode(),
					oInfo.name()
				);
				sLine += sBuffer;

				// Argument(s) bytes
				const int nArgBytes = oInfo.argBytes();
				assert(nArgBytes >= 0 && nArgBytes <= 2);
				if (nArgBytes >= 1)
				{
					sprintf_s<32>(sBuffer, " %02X", pLogItem->argByte1());
					sLine += sBuffer;
				}
				if (nArgBytes == 2)
				{
					sprintf_s<32>(sBuffer, " %02X", pLogItem->argByte2());
					sLine += sBuffer;
				}

				// Newline
				sLine += '\n';

				// Write to file
				fwrite(sLine.data(), 1, sLine.size(), m_pFile);
			}
			break;
		default:
			assert(false && "Unknown log item type");
		}
	}
}