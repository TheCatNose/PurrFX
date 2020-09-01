#pragma once

// GME (Game Music Emu) emulation code wrapper

#include <cstddef>
#include "CNes.h"
#include "DClass.h"
#include "../gme/Nsf_Emu.h"
#include "CLogItemCpuInstruction.h"
#include "CLogItemCodeLabel.h"
#include "CLogItemFrameStart.h"
#include "CLogItemFrameEnd.h"
#include "CLogItemApuRegisterWrite.h"
#include "CAudioProxyBuffer.h"
#include "CAudioProxyBufferDataProvider.h"
#include "CFrameDataProcessor.h"

class CNesGmeAudioDataProvider;

namespace PurrFX
{

	class CNesGme : public CNes, private CGmeIntegrator
	{
	public:
		CNesGme();
		~CNesGme();

		// CNes implementation
		virtual bool open(const pathchar_t* i_sFileName);
		virtual bool open(const uint8_t* i_pData, size_t i_nSize);
		virtual bool setTrack(int i_nTrack);
		virtual int  trackCount() const;
		virtual bool render(char* o_pData, size_t i_nDataSize);

		CLASS_MAKE_NON_COPYABLE(CNesGme)
	private:
		virtual bool prepareEmulator();

		// CGmeIntegrator implementation
		virtual void onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2);
		virtual void onGmeEventCodeLabel(char i_cLabelName);
		virtual void onGmeEventFrameStart(int i_nFrame);
		virtual void onGmeEventFrameEnd();
		virtual void onGmeEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue);
		virtual void onGmeDpcmSampleStarted(uint8_t i_nAddress, uint8_t i_nLength);
		virtual bool gmeGetFrameCode(std::vector<uint8_t>& o_rCode);
		virtual bool gmeActivateDpcmSample(uint8_t i_nAddress, uint8_t i_nLength);

		Music_Emu* m_pEmu = nullptr;
		CAudioProxyBuffer m_oAudioConverter;
	};

}
