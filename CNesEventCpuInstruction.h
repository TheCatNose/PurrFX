#pragma once
// NES event: CPU instruction

#include <cstdint>
#include "DClass.h"
#include "CNesEvent.h"

namespace PurrFX
{
	class CNesEventCpuInstruction: public CNesEvent
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesEventCpuInstruction)
	public:
		CNesEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2);

		uint16_t address() const;
		uint8_t  opcode() const;
		uint8_t  argByte1() const;
		uint8_t  argByte2() const;

		// CNesEvent implementation
		virtual ENesEventType type() const;

	private:
		uint16_t m_nAddress;
		uint8_t  m_nOpcode;
		uint8_t  m_nArgByte1;
		uint8_t  m_nArgByte2;
	};
}