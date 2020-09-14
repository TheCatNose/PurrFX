#pragma once
// NES event: APU register write

#include <cstdint>
#include "DClass.h"
#include "CNesEvent.h"
#include "ECodeLabelType.h"

namespace PurrFX
{
	class CNesEventApuRegisterWrite : public CNesEvent
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesEventApuRegisterWrite)
	public:
		CNesEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue);

		uint16_t registerNumber() const;
		uint8_t  registerValue() const;

		// CNesEvent implementation
		virtual ENesEventType type() const;

	private:
		uint16_t m_nRegister;
		uint8_t  m_nValue;
	};
}