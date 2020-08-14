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

		auto* pItemCpuInstruction = dynamic_cast<const CNesLogItemCpuInstruction*>(i_pLogItem);

		if (pItemCpuInstruction != nullptr)
		{
			fprintf(m_pFile,
				"$%04X: %02X%02X%02X\n",
				pItemCpuInstruction->address(),
				pItemCpuInstruction->opcode(),
				pItemCpuInstruction->arg1(),
				pItemCpuInstruction->arg2()
			);
		}
		else
			assert(false && "Unknown log item type");
	}
}