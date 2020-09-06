#pragma once
// File loading implementation of DPCM data source

#include "DPath.h"
#include "CDpcmDataProvider.h"
#include "CDpcmFile.h"
#include <vector>
#include <map>

namespace PurrFX
{
	class CDpcmDataFileReader: public CDpcmDataProvider
	{
	public:
		CDpcmDataFileReader(bool i_bEnableClassicAccessMode);
		virtual ~CDpcmDataFileReader();

		// CDpcmDataProvider implementation
		virtual const CDpcmSample* getSample(uint8_t i_nAddress, uint8_t i_nLength) const;
		virtual const CDpcmSample* getSample() const;

		bool   setCurrentIndex(size_t i_nCurrentIndex);
		size_t size() const;
		void   load(const pathstring& i_sFileName);

		CLASS_MAKE_NON_COPYABLE(CDpcmDataFileReader)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmDataFileReader)
	private:
		uint16_t key(uint8_t i_nAddress, uint8_t i_nLength) const;

		bool m_bClassicAccessModeEnabled = false;
		
		// Modern access
		std::vector<CDpcmSample*> m_aSamples;
		bool   m_bIsCurrentIndexSet = false;
		size_t m_nCurrentIndex = 0;
		// Classic access
		std::map<uint16_t, CDpcmSample*> m_mSamples;
	};
}