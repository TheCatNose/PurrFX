#include "gme/Music_Emu.h"

#include <iostream>
#include <memory>

void showErrorMessage(const char* i_sMessage)
{
	if (i_sMessage != nullptr)
		std::cout << "Error: " << i_sMessage << std::endl;
}

int main()
{
	//////////////
	// Settings //
	//////////////

	const char* sFileName   = "data/in/Gimmick!.nsf";
	const int   nTrack      = 6;     // track index
	const int   nTime       = 60;    // time in seconds
	const int   nSampleRate = 44100; // sound quality
	
	/////////////////////
	// Setup emulation //
	/////////////////////

	gme_err_t sError = nullptr;

	// Determine file type
	gme_type_t pFileType;
	sError = gme_identify_file(sFileName, &pFileType);
	if (sError != nullptr || pFileType == nullptr || pFileType->system != "Nintendo NES")
	{
		showErrorMessage(sError);
		showErrorMessage("Wrong file type");
		return 1;
	}
	
	// Create emulator
	std::unique_ptr<Music_Emu> pEmu(pFileType->new_emu());
	if (pEmu == nullptr)
	{
		showErrorMessage("Out of memory");
		return 1;
	}

	// Set sample rate
	sError = pEmu->set_sample_rate(nSampleRate);
	if (sError != nullptr)
	{
		showErrorMessage(sError);
		return 1;
	}

	// Load music file
	sError = pEmu->load_file(sFileName);
	if (sError != nullptr)
	{
		showErrorMessage(sError);
		return 1;
	}

	// Start track
	sError = pEmu->start_track(nTrack);
	if (sError != nullptr)
	{
		showErrorMessage(sError);
		return 1;
	}

	////////////////
	// WAV output //
	////////////////

	FILE* pFile = nullptr;
	fopen_s(&pFile, "data/out/out.wav", "wb");
	if (pFile != nullptr)
	{
		// WAV header

		const uint32_t nDataSize = nTime * nSampleRate /* stereo */ * 2 /* bytes per sample */ * 2;
		const int nHdrSize = 44;
		fwrite("RIFF", 1, 4, pFile);
		const uint32_t nFileSize = nDataSize + nHdrSize;
		fwrite(&nFileSize, 1, sizeof(nFileSize), pFile);
		fwrite("WAVE", 1, 4, pFile);
		fwrite("fmt ", 1, 4, pFile);
		const uint32_t nFmtChunkSize = 16;
		fwrite(&nFmtChunkSize, 1, sizeof(nFmtChunkSize), pFile);
		const uint16_t nFormat = 1; // PCM
		fwrite(&nFormat, 1, sizeof(nFormat), pFile);
		uint16_t nChannels = 2; // Stereo
		fwrite(&nChannels, 1, sizeof(nChannels), pFile);
		uint32_t nSampleRate_ = nSampleRate;
		fwrite(&nSampleRate_, 1, sizeof(nSampleRate_), pFile);
		uint16_t nBitsPerSample = 16;
		uint32_t nBitRate = (nSampleRate * nBitsPerSample * nChannels) / 8;
		fwrite(&nBitRate, 1, sizeof(nBitRate), pFile);
		uint16_t nBytesPerSample = (nBitsPerSample * nChannels) / 8;
		fwrite(&nBytesPerSample, 1, sizeof(nBytesPerSample), pFile);
		fwrite(&nBitsPerSample, 1, sizeof(nBitsPerSample), pFile);
		fwrite("data", 1, 4, pFile);
		fwrite(&nDataSize, 1, sizeof(nDataSize), pFile);

		uint32_t nBytesToWrite = nDataSize;

		// WAV data

		while (nBytesToWrite > 0)
		{
			// Prepare buffer
			const uint32_t nBufferSize = 1024;
			short          aBuffer[nBufferSize];
			const uint32_t nBufferBytes = nBufferSize * sizeof(aBuffer[0]);

			// Fill buffer
			sError = pEmu->play(nBufferSize, aBuffer);
			if (sError != nullptr)
			{
				showErrorMessage(sError);
				break;
			}

			// Write to file
			uint32_t nSize = nBufferBytes;
			if (nSize >= nBytesToWrite)
				nSize  = nBytesToWrite;
			fwrite(aBuffer, 1, nSize, pFile);
			nBytesToWrite -= nSize;
		}

		fclose(pFile);
	}
	else
		return 1;

	return 0;
}