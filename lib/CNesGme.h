#pragma once

// GME (Game Music Emu) emulation code wrapper

#include <cstddef>
#include "CNes.h"
#include "DClass.h"
#include "../gme/Nsf_Emu.h"

namespace PurrFX
{

	class CNesGme : public CNes, private CGmeEventsReceiver
	{
	public:
		~CNesGme();

		// CNes implementation
		virtual bool open(const char* i_sFileName);
		virtual bool setTrack(int i_nTrack);
		virtual bool render(char* o_pData, size_t i_nDataSize);

		CLASS_MAKE_NON_COPYABLE(CNesGme);
	private:
		// CGmeLogDataConsumer implementation
		virtual void onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArg1, uint8_t i_nArg2);

		Music_Emu* m_pEmu = nullptr;
	};

}
