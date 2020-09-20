#pragma once
// NES state (i.e. audio related registers)

#include "CFrameData.h"

namespace PurrFX
{
	class CNesState
	{
	public:
		CNesState();

		void update(const CFrameData& i_rFrameData);
		uint8_t get(ERegister i_eRegister) const;

		uint16_t apuPulse1Timer() const;
		uint16_t apuPulse2Timer() const;
		uint16_t apuTriangleTimer() const;

	private:
		CFrameData m_oState;
	};
}