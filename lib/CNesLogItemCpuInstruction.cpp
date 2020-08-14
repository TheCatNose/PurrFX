#include "CNesLogItemCpuInstruction.h"

namespace PurrFX
{
	CNesLogItemCpuInstruction::CNesLogItemCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArg1, uint8_t i_nArg2):
		m_nAddress(i_nAddress),
		m_nOpcode(i_nOpcode),
		m_nArg1(i_nArg1),
		m_nArg2(i_nArg2)
	{
	}

	uint16_t CNesLogItemCpuInstruction::address() const { return m_nAddress; }
	uint8_t  CNesLogItemCpuInstruction::opcode()  const { return m_nOpcode; }
	uint8_t  CNesLogItemCpuInstruction::arg1()    const { return m_nArg1; }
	uint8_t  CNesLogItemCpuInstruction::arg2()    const { return m_nArg2; }
}