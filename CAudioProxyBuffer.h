#pragma once
// Proxy audio buffer with ability to convert bit depth & stereo/mono on the fly
//
// Notes:
// * It won't own data provider
// * Supports 8bit & 16bit bit depth (with CPcmSample class)
// * Supports mono & stereo
//
//                    getData()                         getData()                                                    get data
// [ Audio library ] ----------> [ CAudioProxyBuffer ] ----------> [ CAudioProxyBufferDataProvider implementation ] ----------> [ Audio data source ]

#include <array>
#include <cassert>
#include <cstdint>
#include <limits>
#include "DClass.h"
#include "CAudioProxyBufferDataProvider.h"

namespace PurrFX
{
	class CAudioProxyBuffer
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CAudioProxyBuffer)
		CLASS_MAKE_NON_COPYABLE(CAudioProxyBuffer)
	public:
		CAudioProxyBuffer(int i_nSrcBitDepth, int i_nSrcChannels);

		void reset();
		bool getData(char* o_pDstData, size_t i_nDstSize, int i_nBitDepth, int i_nChannels, CAudioProxyBufferDataProvider* i_pDataProvider);

	private:
		const int    m_nSrcBitDepth;
		const int    m_nSrcChannels;
		const size_t m_nSrcSampleBytes; // For all channels

		std::array<char, 512> m_aSrcData;
		size_t                m_nSrcDataUsed;
	};
}