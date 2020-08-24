#pragma once
// Base class for all frame data receivers

#include <cstdint>
#include "CFrameData.h"

namespace PurrFX
{
	class CFrameDataConsumer
	{
	public:
		virtual ~CFrameDataConsumer();
		
		void startFrame();
		void setRegister(ERegister i_eRegister, uint8_t i_nValue);
		void endFrame();

	private:
		virtual void onFrameDataReady(const CFrameData& i_rFrameData) = 0;

		bool m_bFrameStarted = false;
		CFrameData m_oData;
	};
}