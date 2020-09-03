#pragma once
// Log item for APU register write

#include <cstdint>
#include "DClass.h"
#include "CLogItem.h"
#include "ECodeLabelType.h"

namespace PurrFX
{
	class CLogItemApuRegisterWrite : public CLogItem
	{
	public:
		CLogItemApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue);

		uint16_t registerNumber() const;
		uint8_t  registerValue() const;

		// CLogItem implementation
		virtual ELogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CLogItemApuRegisterWrite);
	private:
		uint16_t m_nRegister;
		uint8_t  m_nValue;
	};
}