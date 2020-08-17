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
		case ENesLogItemType::CodeLabel:
			{
				auto* pLogItem = dynamic_cast<const CNesLogItemCodeLabel*>(i_pLogItem);

				std::string sName;
				switch (pLogItem->labelType())
				{
				case ENesCodeLabelType::InitAddress:
					sName = "init:";
					break;
				case ENesCodeLabelType::PlayAddress:
					sName = "play:";
					break;
				}
				assert(sName != std::string());

				m_oFile.write(sName.data(), sName.size());
				m_oFile.write("\n", 1);
			}
			break;
		case ENesLogItemType::FrameStart:
			{
				auto* pLogItem = dynamic_cast<const CNesLogItemFrameStart*>(i_pLogItem);
				
				char sBuffer[32];
				int nChars = sprintf_s<32>(sBuffer, "frame %d\n", pLogItem->newFrame());
				if (nChars > 0)
					m_oFile.write(sBuffer, nChars);
			}
			break;
		case ENesLogItemType::ApuRegisterWrite:
			{
				auto* pLogItem = dynamic_cast<const CNesLogItemApuRegisterWrite*>(i_pLogItem);
				char sBuffer[32];
				int nChars = sprintf_s<32>(sBuffer, "$%04X <- %02X\n",
					pLogItem->registerNumber(),
					pLogItem->registerValue()
					);
				if (nChars > 0)
					m_oFile.write(sBuffer, nChars);
			}
			break;
		default:
			assert(false && "Unknown log item type");
		}
	}
}