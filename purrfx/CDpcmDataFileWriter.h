#pragma once
// File writing DPCM data consumer

#include <string>
#include "CDpcmDataConsumer.h"

namespace PurrFX
{
	class CDpcmDataFileWriter final: public CDpcmDataConsumer
	{
	public:
		CDpcmDataFileWriter(const char* i_sOutputFolder);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmDataFileWriter)
		CLASS_MAKE_NON_COPYABLE(CDpcmDataFileWriter)
	private:
		// CDpcmDataConsumer implementation
		virtual void onSampleReady(const CDpcmSample& i_rSample);

		std::string m_sOutputFolder;
	};
}