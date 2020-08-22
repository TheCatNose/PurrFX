#include "CLogFileWriter.h"

namespace PurrFX
{
	CLogFileWriter::CLogFileWriter(const char* i_sFileName):
		m_oFile(i_sFileName, CBufferedFileWriter::MAX_BUFFER_SIZE)
	{
	}

	void CLogFileWriter::onNewItem(const CLogItem* i_pLogItem)
	{
		if (!m_oFile.isOpened())
			return;

		switch(i_pLogItem->type())
 		{
		case ELogItemType::CpuInstruction:
			{
				auto* pLogItem = dynamic_cast<const CLogItemCpuInstruction*>(i_pLogItem);
				CCpuInstructionInfo oInfo(pLogItem->opcode());

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
		case ELogItemType::CodeLabel:
			{
				auto* pLogItem = dynamic_cast<const CLogItemCodeLabel*>(i_pLogItem);

				std::string sName;
				switch (pLogItem->labelType())
				{
				case ECodeLabelType::InitAddress:
					sName = "init:";
					break;
				case ECodeLabelType::PlayAddress:
					sName = "play:";
					break;
				}
				assert(sName != std::string());

				m_oFile.write(sName.data(), sName.size());
				m_oFile.write("\n", 1);
			}
			break;
		case ELogItemType::FrameStart:
			{
				auto* pLogItem = dynamic_cast<const CLogItemFrameStart*>(i_pLogItem);
				
				char sBuffer[32];
				int nChars = sprintf_s<32>(sBuffer, "frame %d\n", pLogItem->newFrame());
				if (nChars > 0)
					m_oFile.write(sBuffer, nChars);
			}
			break;
		case ELogItemType::FrameEnd:
			{
				auto* pLogItem = dynamic_cast<const CLogItemFrameEnd*>(i_pLogItem);
				m_oFile.write("frame end\n", 10);
			}
			break;
		case ELogItemType::ApuRegisterWrite:
			{
				auto* pLogItem = dynamic_cast<const CLogItemApuRegisterWrite*>(i_pLogItem);
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