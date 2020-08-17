#pragma once
// NES log item for APU register write

#include <cstdint>
#include "DClass.h"
#include "CNesLogItem.h"
#include "ENesCodeLabelType.h"

namespace PurrFX
{
	class CNesLogItemApuRegisterWrite : public CNesLogItem
	{
	public:
		CNesLogItemApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue);

		uint16_t registerNumber() const;
		uint8_t  registerValue() const;

		// CNesLogItem implementation
		virtual ENesLogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesLogItemApuRegisterWrite);
	private:
		uint16_t m_nRegister;
		uint8_t  m_nValue;
	};
}