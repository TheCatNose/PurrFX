#pragma once
// GME version of CAudioProxyBufferDataProvider

#include "gme/Nsf_Emu.h"
#include "DClass.h"
#include "CAudioProxyBufferDataProvider.h"

namespace PurrFX
{
	class CNesGmeAudioDataProvider: public CAudioProxyBufferDataProvider
	{
	public:
		CNesGmeAudioDataProvider(Music_Emu* i_pEmu);
		virtual bool getData(char* o_pData, size_t i_nDataSize);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesGmeAudioDataProvider)
	private:
		Music_Emu* m_pEmu;
	};
}