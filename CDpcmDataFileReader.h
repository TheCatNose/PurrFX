#pragma once
// File loading implementation of DPCM data source

#include "DPath.h"
#include "CDpcmDataProvider.h"
#include "CDpcmFile.h"
#include "CDpcmStorage.h"

namespace PurrFX
{
	class CDpcmDataFileReader: public CDpcmDataProvider
	{
		CLASS_MAKE_NON_COPYABLE(CDpcmDataFileReader)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmDataFileReader)
	public:
		CDpcmDataFileReader(bool i_bUseClassicAccessMode);

		// CDpcmDataProvider implementation
		virtual const CDpcmSample* getSample(uint8_t i_nAddress, uint8_t i_nLength) const;
		virtual const CDpcmSample* getSample() const;

		bool   setCurrentIndex(size_t i_nCurrentIndex);
		size_t size() const;
		void   load(const pathstring& i_sFileName);

	private:
		CDpcmStorage m_oStorage;
	};
}