#pragma once
// Audio properties/format class

#include "DClass.h"

namespace PurrFX
{
	class CAudioFormat
	{
	public:
		CAudioFormat();
		CAudioFormat(int i_nSampleRate, bool i_bStereo = true, int i_nBitDepth = 16);

		int  sampleRate() const;
		int  channels() const;
		int  bitDepth() const;
		
		int  bytesPerSample() const;

	private:
		int  m_nSampleRate;
		bool m_bStereo;
		int  m_nBitDepth;
	};
}