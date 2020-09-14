#include "CNesEventCpuInstruction.h"

namespace PurrFX
{
	CNesEventCpuInstruction::CNesEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2):
		m_nAddress(i_nAddress),
		m_nOpcode(i_nOpcode),
		m_nArgByte1(i_nArgByte1),
		m_nArgByte2(i_nArgByte2)
	{
	}

	uint16_t CNesEventCpuInstruction::address()  const { return m_nAddress; }
	uint8_t  CNesEventCpuInstruction::opcode()   const { return m_nOpcode; }
	uint8_t  CNesEventCpuInstruction::argByte1() const { return m_nArgByte1; }
	uint8_t  CNesEventCpuInstruction::argByte2() const { return m_nArgByte2; }

	ENesEventType CNesEventCpuInstruction::type() const
	{
		return ENesEventType::CpuInstruction;
	}
}