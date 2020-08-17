#pragma once

// Base class for all NES emulation code wrappers
//
// Notes:
// * It won't own CNesLogDataConsumer instance.

#include <bitset>
#include <cassert>
#include "CNesLogDataConsumer.h"

namespace PurrFX
{

	class CNes
	{
	public:
		virtual ~CNes();

		virtual bool open(const char* i_sName) = 0;
		virtual bool setTrack(int i_nTrack) = 0;
		virtual bool render(char* o_pData, size_t i_nDataSize) = 0;

		bool setSoundOptions(int i_nSampleRate);
		int  soundSampleRate();

		void setLogDataConsumer(CNesLogDataConsumer* i_pConsumer);
		void setLogItemTypeEnabled(ENesLogItemType i_eType);
		void setLogItemTypeDisabled(ENesLogItemType i_eType);

	protected:
		bool logEnabled() const;
		void logAddItem(const CNesLogItem& i_rItem);

	private:
		int m_nSoundSampleRate = 44100;

		CNesLogDataConsumer* m_pLogDataConsumer = nullptr;
		std::bitset<32> m_aLogItemTypesDisabled;
	};

}
