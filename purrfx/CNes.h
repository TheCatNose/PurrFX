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
		virtual bool open(const char* i_pData, size_t i_nSize) = 0;
		virtual bool setTrack(int i_nTrack) = 0;
		virtual bool render(char* o_pData, size_t i_nDataSize) = 0;

		///////////////////
		// Sound options //
		///////////////////

	public:
		bool setSoundOptions(int i_nSampleRate);
		int  soundSampleRate();

	private:
		int m_nSoundSampleRate = 44100;

		/////////////
		// Logging //
		/////////////

	public:
		void setLogDataConsumer(CNesLogDataConsumer* i_pConsumer);
		void logItemTypeEnable(ENesLogItemType i_eType);
		void logItemTypeDisable(ENesLogItemType i_eType);

	protected:
		bool logEnabled() const;
		void logAddItem(const CNesLogItem& i_rItem);

	private:
		CNesLogDataConsumer* m_pLogDataConsumer = nullptr;
		std::bitset<32> m_aLogItemTypesDisabled;
	};

}
