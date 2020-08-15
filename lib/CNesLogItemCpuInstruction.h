#pragma once
// NES log item for CPU instruction

#include <cstdint>
#include "DClass.h"
#include "CNesLogItem.h"

namespace PurrFX
{
	class CNesLogItemCpuInstruction: public CNesLogItem
	{
	public:
		CNesLogItemCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2);

		uint16_t address() const;
		uint8_t  opcode() const;
		uint8_t  argByte1() const;
		uint8_t  argByte2() const;

		// CNesLogItem implementation
		virtual ENesLogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesLogItemCpuInstruction);
	private:
		uint16_t m_nAddress;
		uint8_t  m_nOpcode;
		uint8_t  m_nArgByte1;
		uint8_t  m_nArgByte2;
	};
}