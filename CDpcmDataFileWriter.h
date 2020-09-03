#pragma once
// File writing DPCM data consumer

#include <string>
#include "CDpcmDataConsumer.h"
#include "EDpcmFileType.h"
#include "DPath.h"

namespace PurrFX
{
	class CBufferedFileWriter;

	class CDpcmDataFileWriter final: public CDpcmDataConsumer
	{
	public:
		CDpcmDataFileWriter(const pathchar_t* i_sOutputFolder, EDpcmFileType i_eType);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmDataFileWriter)
		CLASS_MAKE_NON_COPYABLE(CDpcmDataFileWriter)
	private:
		// CDpcmDataConsumer implementation
		virtual void onSampleReady(const CDpcmSample& i_rSample);

		const pathchar_t* fileExtension() const;

		pathstring m_sOutputFolder;
		EDpcmFileType m_eType;
	};
}