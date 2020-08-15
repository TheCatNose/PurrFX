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
				fprintf(m_pFile,
					"$%04X: %02X%02X%02X\n",
					pLogItem->address(),
					pLogItem->opcode(),
					pLogItem->arg1(),
					pLogItem->arg2()
				);
			}
			break;
		default:
			assert(false && "Unknown log item type");
		}
	}
}