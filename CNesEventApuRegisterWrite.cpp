#include "CNesEventApuRegisterWrite.h"

namespace PurrFX
{
	CNesEventApuRegisterWrite::CNesEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue):
		m_nRegister(i_nRegister),
		m_nValue(i_nValue)
	{
	}

	uint16_t CNesEventApuRegisterWrite::registerNumber() const { return m_nRegister; }
	uint8_t  CNesEventApuRegisterWrite::registerValue()  const { return m_nValue; }

	ENesEventType CNesEventApuRegisterWrite::type() const
	{
		return ENesEventType::ApuRegisterWrite;
	}
}