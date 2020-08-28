#pragma once
// File writing DPCM data consumer

#include <string>
#include "CDpcmDataConsumer.h"
#include "EDpcmFileType.h"

namespace PurrFX
{
	class CBufferedFileWriter;

	class CDpcmDataFileWriter final: public CDpcmDataConsumer
	{
	public:
		CDpcmDataFileWriter(const char* i_sOutputFolder, EDpcmFileType i_eType);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmDataFileWriter)
		CLASS_MAKE_NON_COPYABLE(CDpcmDataFileWriter)
	private:
		// CDpcmDataConsumer implementation
		virtual void onSampleReady(const CDpcmSample& i_rSample);


		const char* fileExtension() const;
		void saveAsDmc(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);
		void saveAsRaw(CBufferedFileWriter& i_rFile, const CDpcmSample& i_rSample);

		std::string m_sOutputFolder;
		EDpcmFileType m_eType;
	};
}