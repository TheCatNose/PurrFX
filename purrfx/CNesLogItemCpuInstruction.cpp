#include "CNesLogItemCpuInstruction.h"

namespace PurrFX
{
	CNesLogItemCpuInstruction::CNesLogItemCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2):
		m_nAddress(i_nAddress),
		m_nOpcode(i_nOpcode),
		m_nArgByte1(i_nArgByte1),
		m_nArgByte2(i_nArgByte2)
	{
	}

	uint16_t CNesLogItemCpuInstruction::address()  const { return m_nAddress; }
	uint8_t  CNesLogItemCpuInstruction::opcode()   const { return m_nOpcode; }
	uint8_t  CNesLogItemCpuInstruction::argByte1() const { return m_nArgByte1; }
	uint8_t  CNesLogItemCpuInstruction::argByte2() const { return m_nArgByte2; }

	ENesLogItemType CNesLogItemCpuInstruction::type() const
	{
		return ENesLogItemType::CpuInstruction;
	}
}