#pragma once

// GME (Game Music Emu) emulation code wrapper

#include <cstddef>
#include "CNes.h"
#include "DClass.h"
#include "../gme/Music_Emu.h"

namespace PurrFX
{

	class CNesGme : public CNes
	{
	public:
		~CNesGme();

		// CNes implementation
		virtual bool open(const char* i_sFileName);
		virtual bool setTrack(int i_nTrack);
		virtual bool render(char* o_pData, size_t i_nDataSize);

		MAKE_NON_COPYABLE(CNesGme);
	private:
		Music_Emu* m_pEmu = nullptr;
	};

}
