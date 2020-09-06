#pragma once
// DPCM samples consumer that stores data in memory.
// Also is DPCM samples provider.

#include "DClass.h"
#include "CDpcmDataConsumer.h"
#include "CDpcmDataProvider.h"
#include "CDpcmStorage.h"

namespace PurrFX
{
	class CDpcmDataBuffer: public CDpcmDataConsumer, public CDpcmDataProvider
	{
	public:
		CDpcmDataBuffer(bool i_bUseClassicAccessMode);

		bool   setCurrentIndex(size_t i_nCurrentIndex);
		size_t size() const;

		// CDpcmDataProvider implementation
		virtual const CDpcmSample* getSample(uint8_t i_nAddress, uint8_t i_nLength) const;
		virtual const CDpcmSample* getSample() const;

		CLASS_MAKE_NON_COPYABLE(CDpcmDataBuffer)
		CLASS_USE_DEFAULT_CONSTRUCTOR(CDpcmDataBuffer)
	private:
		// CDpcmDataConsumer implementation
		virtual void onSampleReady(const CDpcmSample& i_rSample);


		CDpcmStorage m_oStorage;
	};
}