#include "CNesPtr.h"
#include "CNesGme.h"

PurrFX::CNesPtr::CNesPtr(ENesType i_eType)
{
	if (i_eType == ENesType::GameMusicEmu)
		m_pNes = new CNesGme;
	assert(m_pNes != nullptr);
}

PurrFX::CNesPtr::~CNesPtr()
{
	delete m_pNes;
}

PurrFX::CNes* PurrFX::CNesPtr::operator->() const
{
	return m_pNes;
}
