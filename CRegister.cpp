#include "CRegister.h"
#include "CRegisterStructure.h"

PurrFX::CRegister::CRegister(PurrFX::ERegister i_eRegister, uint8_t i_nValue)
{
	m_eRegister = i_eRegister;
	m_nValue    = i_nValue;
}

PurrFX::ERegister PurrFX::CRegister::type() const
{
	return m_eRegister;
}

uint8_t PurrFX::CRegister::value() const
{
	return m_nValue;
}

uint8_t PurrFX::CRegister::get(char i_cName) const
{
	const CRegisterStructure& rStructure = CRegisterStructure::get(m_eRegister);
	for (size_t i = 0; i < rStructure.fieldCount(); i++)
		if (rStructure.name(i) == i_cName)
		{
			uint8_t nValue = m_nValue >> rStructure.firstBit(i);
			return nValue & mask(rStructure,i);
		}
	assert(false && "Unknown NES register field name");
	return 0;
}

bool PurrFX::CRegister::set(char i_cName, uint8_t i_nValue)
{
	const CRegisterStructure& rStructure = CRegisterStructure::get(m_eRegister);
	for (size_t i = 0; i < rStructure.fieldCount(); i++)
		if (rStructure.name(i) == i_cName)
		{
			// Clear field
			m_nValue &= ~(mask(rStructure,i) << rStructure.firstBit(i));
			// Set new value
			i_nValue  &= mask(rStructure,i);
			i_nValue <<= rStructure.firstBit(i);
			m_nValue |= i_nValue;

			return true;
		}
	assert(false && "Unknown NES register field name");
	return false;
}

uint8_t PurrFX::CRegister::mask(const PurrFX::CRegisterStructure& i_rStructure, size_t i_nFieldIndex) const
{
	static const uint8_t aMasks[] = {
		0b00000001,
		0b00000011,
		0b00000111,
		0b00001111,
		0b00011111,
		0b00111111,
		0b01111111,
		0b11111111,
	};
	return aMasks[ i_rStructure.size(i_nFieldIndex)-1 ];
}
