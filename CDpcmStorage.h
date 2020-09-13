#pragma once
// Simple DPCM data storage for DPCM data prodivers
// Owns all added audio samples

#include <vector>
#include <map>
#include <cstdint>
#include <cstddef>
#include "DClass.h"
#include "CDpcmSample.h"

namespace PurrFX
{
	class CDpcmStorage
	{
		CLASS_MAKE_NON_COPYABLE(CDpcmStorage)
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CDpcmStorage)
	public:
		CDpcmStorage(bool i_bUseClassicAccessMode);
		~CDpcmStorage();

		void add(CDpcmSample* i_pSample);

		// For classic access mode
		const CDpcmSample* get(uint8_t i_nAddress, uint8_t i_nLength) const;

		// For modern access mode
		const CDpcmSample* get() const;
		const bool del(size_t i_nIndex);
		size_t size() const;
		bool setCurrent(size_t i_nIndex);
	
	private:
		uint16_t key(uint8_t i_nAddress, uint8_t i_nLength) const;

		bool m_bUseClassicAccessMode = false;

		// Modern access
		std::vector<CDpcmSample*> m_aSamples;
		bool   m_bIsCurrentIndexSet = false;
		size_t m_nCurrentIndex = 0;
		// Classic access
		std::map<uint16_t, CDpcmSample*> m_mSamples;
	};
}