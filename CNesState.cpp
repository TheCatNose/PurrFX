#include "CNesState.h"
#include "CNesCalculations.h"

PurrFX::CNesState::CNesState()
{
}

void PurrFX::CNesState::update(const CFrameData& i_rFrameData)
{
	for (size_t i = 0; i < RegisterCount; i++)
	{
		ERegister eRegister = ERegister(i);
		if (i_rFrameData.isSet(eRegister))
			m_oState.set( i_rFrameData.getRegister(eRegister) );
	}
}

uint8_t PurrFX::CNesState::get(ERegister i_eRegister) const
{
	return m_oState.get(i_eRegister);
}

uint16_t PurrFX::CNesState::apuPulse1Timer() const
{
	return CNesCalculations::makeApuPulseTimer(
		get(PurrFX::ERegister::Apu4002),
		get(PurrFX::ERegister::Apu4003)
		);
}

uint16_t PurrFX::CNesState::apuPulse2Timer() const
{
	return CNesCalculations::makeApuPulseTimer(
		get(PurrFX::ERegister::Apu4006),
		get(PurrFX::ERegister::Apu4007)
		);
}

uint16_t PurrFX::CNesState::apuTriangleTimer() const
{
	return CNesCalculations::makeApuTriangleTimer(
		get(PurrFX::ERegister::Apu400A),
		get(PurrFX::ERegister::Apu400B)
		);
}
