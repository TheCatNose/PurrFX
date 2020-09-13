#pragma once
// Base class for all DPCM data receivers

#include <cstdint>
#include <list>
#include <vector>
#include <cassert>
#include "DClass.h"

namespace PurrFX
{
	class CDpcmSample;

	class CDpcmDataConsumer
	{
		CLASS_MAKE_NON_COPYABLE(CDpcmDataConsumer)
		CLASS_USE_DEFAULT_CONSTRUCTOR(CDpcmDataConsumer)
	public:
		virtual ~CDpcmDataConsumer();

		// Start -> bytes -> end
		void start(uint8_t i_nAddress, uint8_t i_nLength);
		void addByte(uint8_t i_nValue);
		void end();

	protected:
		virtual void onSampleReady(const CDpcmSample& i_rSample) = 0;

	private:
		bool sampleStarted() const;

		std::list<CDpcmSample*> m_lData;

		CDpcmSample* m_pCurrentSample         = nullptr;
		size_t       m_nCurrentSampleBytesSet = 0;
	};
}