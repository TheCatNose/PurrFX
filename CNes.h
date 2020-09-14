#pragma once

// Base class for all NES emulation code wrappers
//
// Notes:
// * It won't own CNesEventConsumer instance.
// * It won't own CAudioDataConsumer instance.
// * It won't own CFrameDataConsumer instance.
// * It won't own CFrameDataProducer instance.
// * It won't own CDpcmDataConsumer instance.
// * It won't own CDpcmDataProvider instance.

#include <bitset>
#include <cassert>
#include "CAudioFormat.h"
#include "CNesEventConsumer.h"
#include "CAudioDataConsumer.h"
#include "CFrameDataConsumer.h"
#include "CFrameDataProducer.h"
#include "CDpcmDataConsumer.h"
#include "CDpcmDataProvider.h"
#include "DPath.h"

namespace PurrFX
{

	class CNes
	{
	public:
		virtual ~CNes();

		bool         open();                                           // open template based in-memory stored NSF file
		virtual bool open(const pathstring& i_sName) = 0;                    // open NSF file
		virtual bool open(const uint8_t* i_pData, size_t i_nSize) = 0; // open in-memory stored NSF file
		virtual bool setTrack(int i_nTrack) = 0;
		virtual int  trackCount() const = 0;
		virtual bool render(char* o_pData, size_t i_nDataSize) = 0;

		void detachAll(); // Detach all producers/providers/consumers etc

		///////////////////
		// Audio options //
		///////////////////

	public:
		bool                setAudioFormat(const CAudioFormat& i_rFormat);
		const CAudioFormat&    audioFormat();

	private:
		CAudioFormat m_oAudioFormat = CAudioFormat::defaultFormat();

		//////////////////////////
		// Audio data consuming //
		//////////////////////////

	public:
		bool render();
		void setAudioDataConsumer(CAudioDataConsumer* i_pConsumer);
		bool usesAudioDataConsumer() const;

	private:
		CAudioDataConsumer* m_pAudioDataConsumer = nullptr;

		////////////////
		// NES events //
		////////////////

	public:
		void setNesEventConsumer(CNesEventConsumer* i_pConsumer);
		void nesEventTypeEnable(ENesEventType i_eType);
		void nesEventTypeDisable(ENesEventType i_eType);

	protected:
		bool nesEventHandlingEnabled() const;
		void handleNesEvent(const CNesEvent& i_rItem);

	private:
		CNesEventConsumer* m_pNesEventConsumer = nullptr;
		std::bitset<32> m_aNesEventTypesDisabled;

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

		////////////////////////////
		// DPCM data input/output //
		////////////////////////////

	public:
		void setDpcmDataConsumer(CDpcmDataConsumer* i_pConsumer);
		void setDpcmDataProvider(CDpcmDataProvider* i_pProvider);

	protected:
		CDpcmDataConsumer*     dpcmDataConsumer() const;
		bool               usesDpcmDataConsumer() const;
		CDpcmDataProvider*     dpcmDataProvider() const;
		bool               usesDpcmDataProvider() const;

	private:
		CDpcmDataConsumer* m_pDpcmDataConsumer = nullptr;
		CDpcmDataProvider* m_pDpcmDataProvider = nullptr;
	};

}
