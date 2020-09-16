#include "CFrameData.h"

PurrFX::CFrameData::CFrameData()
{
	reset();
}

void PurrFX::CFrameData::reset()
{
	m_aSetMarks.reset();
	for (size_t i = 0; i < RegisterCount; i++)
		m_aValues[i] = 0;
}

void PurrFX::CFrameData::set(ERegister i_eRegister, uint8_t i_nValue)
{
	m_aSetMarks.set( index(i_eRegister) );
	m_aValues[ index(i_eRegister) ] = i_nValue;
}

bool PurrFX::CFrameData::isSet(ERegister i_eRegister) const
{
	return m_aSetMarks.test( index(i_eRegister) );
}

uint8_t PurrFX::CFrameData::get(ERegister i_eRegister) const
{
	return m_aValues[ index(i_eRegister) ];
}

PurrFX::CRegister PurrFX::CFrameData::getRegister(PurrFX::ERegister i_eRegister) const
{
	return CRegister(i_eRegister, get(i_eRegister));
}

void PurrFX::CFrameData::set(const PurrFX::CRegister& i_rRegister)
{
	set(i_rRegister.type(), i_rRegister.value());
}

inline size_t PurrFX::CFrameData::index(ERegister i_eRegister) const
{
	return size_t(i_eRegister);
}
