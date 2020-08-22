#pragma once

// Base class for all NES emulation code wrappers
//
// Notes:
// * It won't own CLogDataConsumer instance.
// * It won't own CAudioDataConsumer instance.

#include <bitset>
#include <cassert>
#include "CAudioFormat.h"
#include "CLogDataConsumer.h"
#include "CAudioDataConsumer.h"

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
		// Audio options //
		///////////////////

	public:
		void                setAudioFormat(const CAudioFormat& i_rFormat);
		const CAudioFormat&    audioFormat();

	private:
		CAudioFormat m_oAudioFormat;

		//////////////////////////
		// Audio data consuming //
		//////////////////////////

	public:
		bool render();
		void setAudioDataConsumer(CAudioDataConsumer* i_pConsumer);
		bool usesAudioDataConsumer() const;

	private:
		CAudioDataConsumer* m_pAudioDataConsumer = nullptr;

		/////////////
		// Logging //
		/////////////

	public:
		void setLogDataConsumer(CLogDataConsumer* i_pConsumer);
		void logItemTypeEnable(ELogItemType i_eType);
		void logItemTypeDisable(ELogItemType i_eType);

	protected:
		bool logEnabled() const;
		void logAddItem(const CLogItem& i_rItem);

	private:
		CLogDataConsumer* m_pLogDataConsumer = nullptr;
		std::bitset<32> m_aLogItemTypesDisabled;
	};

}
