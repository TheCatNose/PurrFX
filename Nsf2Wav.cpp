#include <iostream>
#include "lib/CNesGme.h"
#include "CDataPath.h"

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

	const char* sInputFile  = "Gimmick!.nsf";
	const char* sOutputFile = "out.wav";
	const int   nTrack      = 6;     // track index
	const int   nTime       = 60;    // time in seconds
	const int   nSampleRate = 44100; // sound quality
	
	/////////////////////
	// Setup emulation //
	/////////////////////

	PurrFX::CNesGme oNes;
	if (!oNes.setSoundOptions(nSampleRate))
	{
		showErrorMessage("Can't set sound options");
		return 1;
	}
	std::string sInputPath = CDataPath::inputFile(sInputFile);
	if (!oNes.open( sInputPath.data() ))
	{
		showErrorMessage("Can't open file");
		return 1;
	}
	if (!oNes.setTrack(nTrack))
	{
		showErrorMessage("Can't set track");
		return 1;
	}

	////////////////
	// WAV output //
	////////////////

	std::string sOutputPath = CDataPath::outputFile(sOutputFile);

	FILE* pFile = nullptr;
	fopen_s(&pFile, sOutputPath.data(), "wb");
	if (pFile == nullptr)
	{
		showErrorMessage("Can't create output file");
		return 1;
	}

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
		char           aBuffer[nBufferSize];

		// Fill buffer
		if (!oNes.render(aBuffer, nBufferSize))
		{
			showErrorMessage("Rendering error");
			fclose(pFile);
			return 1;
		}

		// Write to file
		uint32_t nSize = nBufferSize;
		if (nSize >= nBytesToWrite)
			nSize  = nBytesToWrite;
		fwrite(aBuffer, 1, nSize, pFile);
		nBytesToWrite -= nSize;
	}

	fclose(pFile);

	std::cout << "Success!" << std::endl;
	return 0;
}