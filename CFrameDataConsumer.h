#pragma once
// Base class for all frame data receivers

#include <cstdint>
#include <cstddef>
#include <cassert>
#include "CFrameData.h"
#include "DClass.h"

namespace PurrFX
{
	class CFrameDataConsumer
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFrameDataConsumer)

	public:
		static const size_t UnlimitedSize = 0;

		CFrameDataConsumer(size_t i_nSize = UnlimitedSize);
		virtual ~CFrameDataConsumer();
		
		void startFrame();
		void setRegister(ERegister i_eRegister, uint8_t i_nValue);
		void endFrame();

		bool finished() const;

	protected:
		size_t framesProcessed() const;

	private:
		virtual void onFrameDataReady(const CFrameData& i_rFrameData) = 0;

		bool m_bFrameStarted = false;
		size_t m_nSize = 0;
		size_t m_nFramesProcessed = 0;
		CFrameData m_oData;
	};
}