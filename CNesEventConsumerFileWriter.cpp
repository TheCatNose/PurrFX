#include "CNesEventConsumerFileWriter.h"

namespace PurrFX
{
	CNesEventConsumerFileWriter::CNesEventConsumerFileWriter(const pathstring& i_sFileName):
		m_oFile(i_sFileName, CBufferedFileWriter::MAX_BUFFER_SIZE)
	{
	}

	void CNesEventConsumerFileWriter::onEvent(const CNesEvent* i_pEvent)
	{
		if (!m_oFile.isOpened())
			return;

		switch(i_pEvent->type())
 		{
		case ENesEventType::CpuInstruction:
			{
				auto* pEvent = dynamic_cast<const CNesEventCpuInstruction*>(i_pEvent);
				CCpuInstructionInfo oInfo(pEvent->opcode());

				char sBuffer[33];
				int nChars;

				// Address, opcode, name
				nChars = snprintf(sBuffer, 32,
					"$%04X: %02X (%s)",
					pEvent->address(),
					pEvent->opcode(),
					oInfo.name()
				);
				if (nChars > 0)
					m_oFile.write(sBuffer, nChars);

				// Argument(s) bytes
				const int nArgBytes = oInfo.argBytes();
				assert(nArgBytes >= 0 && nArgBytes <= 2);
				if (nArgBytes >= 1)
				{
					nChars = snprintf(sBuffer, 32, " %02X", pEvent->argByte1());
					if (nChars > 0)
						m_oFile.write(sBuffer, nChars);
				}
				if (nArgBytes == 2)
				{
					nChars = snprintf(sBuffer, 32, " %02X", pEvent->argByte2());
					if (nChars > 0)
						m_oFile.write(sBuffer, nChars);
				}

				// Newline
				m_oFile.write("\n", 1);
			}
			break;
		case ENesEventType::CodeLabel:
			{
				auto* pEvent = dynamic_cast<const CNesEventCodeLabel*>(i_pEvent);

				std::string sName;
				switch (pEvent->labelType())
				{
				case ECodeLabelType::InitAddress:
					sName = "init:";
					break;
				case ECodeLabelType::PlayAddress:
					sName = "play:";
					break;
				case ECodeLabelType::Undefined:
					break;
				}
				assert(sName != std::string());

				m_oFile.write(sName.data(), sName.size());
				m_oFile.write("\n", 1);
			}
			break;
		case ENesEventType::FrameStart:
			{
				auto* pEvent = dynamic_cast<const CNesEventFrameStart*>(i_pEvent);
				
				char sBuffer[33];
				int nChars = snprintf(sBuffer, 32, "frame %d\n", pEvent->newFrame());
				if (nChars > 0)
					m_oFile.write(sBuffer, nChars);
			}
			break;
		case ENesEventType::FrameEnd:
			{
				m_oFile.write("frame end\n", 10);
			}
			break;
		case ENesEventType::ApuRegisterWrite:
			{
				auto* pEvent = dynamic_cast<const CNesEventApuRegisterWrite*>(i_pEvent);
				char sBuffer[33];
				int nChars = snprintf(sBuffer, 32, "$%04X <- %02X\n",
					pEvent->registerNumber(),
					pEvent->registerValue()
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