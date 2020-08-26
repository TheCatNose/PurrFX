#pragma once

// Base class for all NES emulation code wrappers
//
// Notes:
// * It won't own CLogDataConsumer instance.
// * It won't own CAudioDataConsumer instance.
// * It won't own CFrameDataConsumer instance.
// * It won't own CFrameDataProducer instance.

#include <bitset>
#include <cassert>
#include "CAudioFormat.h"
#include "CLogDataConsumer.h"
#include "CAudioDataConsumer.h"
#include "CFrameDataConsumer.h"
#include "CFrameDataProducer.h"

namespace PurrFX
{

	class CNes
	{
	public:
		virtual ~CNes();

		virtual bool open(const char* i_sName) = 0;
		virtual bool open(const uint8_t* i_pData, size_t i_nSize) = 0;
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

		/////////////////////////////
		// Frame data input/output //
		/////////////////////////////

	public:
		void setFrameDataConsumer(CFrameDataConsumer* i_pConsumer);
		void setFrameDataProducer(CFrameDataProducer* i_pProducer);

	protected:
		CFrameDataConsumer*     frameDataConsumer() const;
		bool                usesFrameDataConsumer() const;
		CFrameDataProducer*     frameDataProducer() const;
		bool                usesFrameDataProducer() const;

	private:
		CFrameDataConsumer* m_pFrameDataConsumer = nullptr;
		CFrameDataProducer* m_pFrameDataProducer = nullptr;
	};

}
