#include "CLogItemApuRegisterWrite.h"

namespace PurrFX
{
	CLogItemApuRegisterWrite::CLogItemApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue):
		m_nRegister(i_nRegister),
		m_nValue(i_nValue)
	{
	}

	uint16_t CLogItemApuRegisterWrite::registerNumber() const { return m_nRegister; }
	uint8_t  CLogItemApuRegisterWrite::registerValue()  const { return m_nValue; }

	ELogItemType CLogItemApuRegisterWrite::type() const
	{
		return ELogItemType::ApuRegisterWrite;
	}
}