#pragma once
// Base class for every audio data consumer

#include <cassert>
#include <cstdint>
#include "DClass.h"
#include "CAudioFormat.h"

namespace PurrFX
{
	class CAudioDataConsumer
	{
	public:
		CAudioDataConsumer(uint32_t i_nDuration);
		virtual ~CAudioDataConsumer();

		bool finished() const;
		uint32_t bytesToProcess() const;

		void start(const CAudioFormat& i_rAudioFormat);
		void processData(const char* i_pData, uint32_t i_nSize);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CAudioDataConsumer);
	private:
		virtual void onStart(const CAudioFormat& i_rAudioFormat, uint32_t i_nBytesToProcess) = 0;
		virtual void onData(const char* i_pData, uint32_t i_nSize) = 0;
	
	private:
		uint32_t m_nDuration;
		uint32_t m_nBytesToProcess = 0;
	};
}