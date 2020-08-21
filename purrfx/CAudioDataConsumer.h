#pragma once
// Base class for every audio data consumer
//
// TODO: Support different sound options (8bit, mono)

#include <cassert>
#include <cstdint>
#include "DClass.h"

namespace PurrFX
{
	class CAudioDataConsumer
	{
	public:
		CAudioDataConsumer(uint32_t i_nDuration);
		virtual ~CAudioDataConsumer();

		bool finished() const;
		uint32_t bytesToProcess() const;

		void start(int i_nSampleRate);
		void processData(const char* i_pData, uint32_t i_nSize);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CAudioDataConsumer);
	private:
		virtual void onStart(int i_nSampleRate, uint32_t i_nBytesToProcess) = 0;
		virtual void onData(const char* i_pData, uint32_t i_nSize) = 0;
	
	private:
		uint32_t m_nDuration;
		uint32_t m_nBytesToProcess = 0;
	};
}