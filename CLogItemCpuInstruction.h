#pragma once
// Log item for CPU instruction

#include <cstdint>
#include "DClass.h"
#include "CLogItem.h"

namespace PurrFX
{
	class CLogItemCpuInstruction: public CLogItem
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CLogItemCpuInstruction)
	public:
		CLogItemCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2);

		uint16_t address() const;
		uint8_t  opcode() const;
		uint8_t  argByte1() const;
		uint8_t  argByte2() const;

		// CLogItem implementation
		virtual ELogItemType type() const;

	private:
		uint16_t m_nAddress;
		uint8_t  m_nOpcode;
		uint8_t  m_nArgByte1;
		uint8_t  m_nArgByte2;
	};
}