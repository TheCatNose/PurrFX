#pragma once
// Canonical implementation of CDpcmDataProvider

#include "CDpcmDataProvider.h"
#include <vector>
#include <map>

namespace PurrFX
{
	class CDpcmDataProviderStd: public CDpcmDataProvider
	{
	public:
		CDpcmDataProviderStd(bool i_bEnableClassicAccessMode);
		virtual ~CDpcmDataProviderStd();

		// CDpcmDataProvider implementation
		virtual const CDpcmSample* getSample(uint8_t i_nAddress, uint8_t i_nLength) const;
		virtual const CDpcmSample* getSample() const;

		bool   setCurrentIndex(size_t i_nCurrentIndex);
		size_t size() const;
		void   add(CDpcmSample* i_pSample);
		bool   del(size_t i_nCurrentIndex);

		CLASS_MAKE_NON_COPYABLE(CDpcmDataProviderStd)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmDataProviderStd)
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