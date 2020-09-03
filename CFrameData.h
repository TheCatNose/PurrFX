#pragma once
// Register values for one frame

#include <bitset>
#include <cstdint>
#include "DClass.h"
#include "ERegister.h"

namespace PurrFX
{
	class CFrameData
	{
	public:
		CFrameData();

		void reset();

		void      set(ERegister i_eRegister, uint8_t i_nValue);
		bool    isSet(ERegister i_eRegister) const;
		uint8_t   get(ERegister i_eRegister) const;
		
	private:
		inline size_t index(ERegister i_eRegister) const;

		std::bitset<RegisterCount> m_aSetMarks;
		uint8_t                    m_aValues[RegisterCount];
	};
}