#pragma once
// Structure of a register (data fields)

#include <cassert>
#include <string>
#include <cstddef>
#include "DClass.h"
#include "ERegister.h"

namespace PurrFX
{
	class CRegisterStructure final
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CRegisterStructure)
	public:
		static const CRegisterStructure& get(ERegister i_eRegister);

		size_t fieldCount() const;
		char   name    (size_t i_nFieldIndex) const;
		size_t firstBit(size_t i_nFieldIndex) const;
		size_t size    (size_t i_nFieldIndex) const;

	private:
		static const size_t ByteSize = 8;
		size_t m_nFieldCount = 0;
		char   m_aName    [ByteSize] = {'\0','\0','\0','\0','\0','\0','\0','\0'};
		size_t m_aFirstBit[ByteSize] = {0,0,0,0,0,0,0,0};
		size_t m_aSize    [ByteSize] = {0,0,0,0,0,0,0,0};


		CRegisterStructure(ERegister i_eRegister);
		static const char*        sm_aDefinitions[RegisterCount];
		static CRegisterStructure sm_aStructures[RegisterCount];
	};
}