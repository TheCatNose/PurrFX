#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <cassert>
#include <array>
#include "DClass.h"
#include "CAudioFormat.h"

namespace PurrFX
{
	class CWavHeader
	{
		static const size_t HeaderSize = 44;
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CWavHeader)
	public:
		CWavHeader(uint32_t i_nDataSize, const CAudioFormat& i_rFormat);
		CWavHeader(const uint8_t* i_pData);

		size_t size() const;
		bool   isValid() const;

		size_t       dataSize() const;
		CAudioFormat audioFormat() const;

		typedef std::array<uint8_t, CWavHeader::HeaderSize> DataArray;
		void get(DataArray& o_rData) const;

	private:
		uint32_t byteRate() const;
		uint32_t bytesPerSample() const;

		struct CData
		{
			char     sRiff[4];
			uint32_t nFileSize;
			char     sWave[4];
			char     sFmt[4];
			uint32_t nFmtChunkSize;
			uint16_t nFormat;
			uint16_t nChannels;
			uint32_t nSampleRate;
			uint32_t nByteRate;
			uint16_t nBytesPerSample;
			uint16_t nBitsPerSample;
			char     sData[4];
			uint32_t nDataSize;
		} m_oData;

		// Consts
		static constexpr const char* ITEM_RIFF = "RIFF";
		static constexpr const char* ITEM_WAVE = "WAVE";
		static constexpr const char* ITEM_FMT  = "fmt ";
		static constexpr const char* ITEM_DATA = "data";
		static const uint16_t PCM = 1;
		static const uint32_t FMT_CHUNK_SIZE = 16;
	};
}