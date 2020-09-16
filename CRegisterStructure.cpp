#include "CRegisterStructure.h"

const PurrFX::CRegisterStructure& PurrFX::CRegisterStructure::get(PurrFX::ERegister i_eRegister)
{
	return sm_aStructures[size_t(i_eRegister)];
}

size_t PurrFX::CRegisterStructure::fieldCount() const
{
	return m_nFieldCount;
}

char PurrFX::CRegisterStructure::name(size_t i_nFieldIndex) const
{
	assert(i_nFieldIndex < m_nFieldCount);
	return m_aName[i_nFieldIndex];
}

size_t PurrFX::CRegisterStructure::firstBit(size_t i_nFieldIndex) const
{
	assert(i_nFieldIndex < m_nFieldCount);
	return m_aFirstBit[i_nFieldIndex];
}

size_t PurrFX::CRegisterStructure::size(size_t i_nFieldIndex) const
{
	assert(i_nFieldIndex < m_nFieldCount);
	return m_aSize[i_nFieldIndex];
}

PurrFX::CRegisterStructure::CRegisterStructure(PurrFX::ERegister i_eRegister)
{
	const char* sDefinition = sm_aDefinitions[size_t(i_eRegister)];
	assert( strlen(sDefinition) == ByteSize );

	char cPrevName = 0;
	for (size_t nBit = 0; nBit < 8; nBit++)
	{

		const size_t nBitChar = 7-nBit;
		const char cName = sDefinition[nBitChar];
		if (cName == '-')
			continue;

		if (cName == cPrevName)
		{
			assert(m_nFieldCount > 0);
			m_aSize[m_nFieldCount-1]++;
		}
		else
		{
			m_aName    [m_nFieldCount] = cName;
			m_aSize    [m_nFieldCount] = 1;
			m_aFirstBit[m_nFieldCount] = nBit;
			
			m_nFieldCount++;
		}

		cPrevName = cName;
	}
}

const char* PurrFX::CRegisterStructure::sm_aDefinitions[PurrFX::RegisterCount] = {
		/////////
		// APU //
		/////////

		// Pulse 1
		"DDLCVVVV",
		"EPPPNSSS",
		"TTTTTTTT",
		"LLLLLTTT",
		// Pulse 2
		"DDLCVVVV",
		"EPPPNSSS",
		"TTTTTTTT",
		"LLLLLTTT",
		// Triangle
		"CRRRRRRR",
		"TTTTTTTT",
		"LLLLLTTT",
		// Noise
		"--LCVVVV",
		"L---PPPP",
		"LLLLL---",
		// DMC
		"IL--RRRR",
		"-DDDDDDD",
		"AAAAAAAA",
		"LLLLLLLL",
		// Status
		"---DNT21",
};

PurrFX::CRegisterStructure PurrFX::CRegisterStructure::sm_aStructures[PurrFX::RegisterCount] = 
{
		/////////
		// APU //
		/////////

		// Pulse 1
		CRegisterStructure(PurrFX::ERegister::Apu4000),
		CRegisterStructure(PurrFX::ERegister::Apu4001),
		CRegisterStructure(PurrFX::ERegister::Apu4002),
		CRegisterStructure(PurrFX::ERegister::Apu4003),
		// Pulse 2
		CRegisterStructure(PurrFX::ERegister::Apu4004),
		CRegisterStructure(PurrFX::ERegister::Apu4005),
		CRegisterStructure(PurrFX::ERegister::Apu4006),
		CRegisterStructure(PurrFX::ERegister::Apu4007),
		// Triangle
		CRegisterStructure(PurrFX::ERegister::Apu4008),
		CRegisterStructure(PurrFX::ERegister::Apu400A),
		CRegisterStructure(PurrFX::ERegister::Apu400B),
		// Noise
		CRegisterStructure(PurrFX::ERegister::Apu400C),
		CRegisterStructure(PurrFX::ERegister::Apu400E),
		CRegisterStructure(PurrFX::ERegister::Apu400F),
		// DMC
		CRegisterStructure(PurrFX::ERegister::Apu4010),
		CRegisterStructure(PurrFX::ERegister::Apu4011),
		CRegisterStructure(PurrFX::ERegister::Apu4012),
		CRegisterStructure(PurrFX::ERegister::Apu4013),
		// Status
		CRegisterStructure(PurrFX::ERegister::Apu4015),
};