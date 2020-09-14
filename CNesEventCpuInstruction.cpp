#include "CLogItemCpuInstruction.h"

namespace PurrFX
{
	CLogItemCpuInstruction::CLogItemCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2):
		m_nAddress(i_nAddress),
		m_nOpcode(i_nOpcode),
		m_nArgByte1(i_nArgByte1),
		m_nArgByte2(i_nArgByte2)
	{
	}

	uint16_t CLogItemCpuInstruction::address()  const { return m_nAddress; }
	uint8_t  CLogItemCpuInstruction::opcode()   const { return m_nOpcode; }
	uint8_t  CLogItemCpuInstruction::argByte1() const { return m_nArgByte1; }
	uint8_t  CLogItemCpuInstruction::argByte2() const { return m_nArgByte2; }

	ELogItemType CLogItemCpuInstruction::type() const
	{
		return ELogItemType::CpuInstruction;
	}
}