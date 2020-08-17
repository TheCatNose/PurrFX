#include "CNesLogItemApuRegisterWrite.h"

namespace PurrFX
{
	CNesLogItemApuRegisterWrite::CNesLogItemApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue):
		m_nRegister(i_nRegister),
		m_nValue(i_nValue)
	{
	}

	uint16_t CNesLogItemApuRegisterWrite::registerNumber() const { return m_nRegister; }
	uint8_t  CNesLogItemApuRegisterWrite::registerValue()  const { return m_nValue; }

	ENesLogItemType CNesLogItemApuRegisterWrite::type() const
	{
		return ENesLogItemType::ApuRegisterWrite;
	}
}