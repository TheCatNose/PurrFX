#pragma once
// Register value class with access to its data fields

#include <cstdint>
#include "DClass.h"
#include "ERegister.h"

namespace PurrFX
{
	class CRegisterStructure;

	class CRegister final
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CRegister)
	public:
		CRegister(ERegister i_eRegister, uint8_t i_nValue = 0);

		ERegister type() const;
		uint8_t   value() const;

		uint8_t get(char i_cName) const;
		bool    set(char i_cName, uint8_t i_nValue);
		
		uint8_t max(char i_cName) const;

	private:
		uint8_t mask(const CRegisterStructure& i_rStructure, size_t i_nFieldIndex) const;

		ERegister m_eRegister;
		uint8_t   m_nValue;
	};
};
