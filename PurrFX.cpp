// PurrFX demo

#include <iostream>
#include <string>

#include "purrfx/CNesGme.h"
#include "purrfx/CNesLogFileWriter.h"

void showErrorMessage(const char* i_sMessage)
{
	if (i_sMessage != nullptr)
		std::cout << "Error: " << i_sMessage << std::endl;
}
std::string inputPath (const std::string& i_sFileName) { return std::string("data/in/") + i_sFileName; }
std::string outputPath(const std::string& i_sFileName) { return std::string("data/out/") + i_sFileName; }

// Choose demo mode here:
//#define DEMO_MODE_WAV_OUT
#define DEMO_MODE_LOG

int main()
{
	//////////////
	// Settings //
	//////////////

	std::string sInputFile  = "Gimmick!.nsf";
	std::string sOutputFile = "out";
	const int   nTrack      = 6;     // track index
	const int   nTime       = 60;    // time in seconds
	const int   nSampleRate = 44100; // sound quality

#if defined (DEMO_MODE_WAV_OUT)
	sOutputFile += ".wav";
#elif defined (DEMO_MODE_LOG)
	sOutputFile += ".log";
#endif
	
	/////////////////////
	// Setup emulation //
	/////////////////////

	std::string sOutputPath = outputPath(sOutputFile);

	PurrFX::CNesGme oNes;
	PurrFX::CNes* pNes = &oNes;

#if defined (DEMO_MODE_LOG)
	pNes->logItemTypeDisable(PurrFX::ENesLogItemType::CpuInstruction);
	pNes->logItemTypeDisable(PurrFX::ENesLogItemType::CodeLabel);
	pNes->logItemTypeDisable(PurrFX::ENesLogItemType::FrameEnd);
	PurrFX::CNesLogFileWriter oLogWriter( sOutputPath.data() );
	pNes->setLogDataConsumer(&oLogWriter);
#endif
	if (!pNes->setSoundOptions(nSampleRate))
	{
		showErrorMessage("Can't set sound options");
		return 1;
	}
	std::string sInputPath = inputPath(sInputFile);
	if (!pNes->open( sInputPath.data() ))
	{
		showErrorMessage("Can't open file");
		return 1;
	}
	if (!pNes->setTrack(nTrack))
	{
		showErrorMessage("Can't set track");
		return 1;
	}

	////////////
	// Output //
	////////////

	const uint32_t nDataSize = nTime * nSampleRate /* stereo */ * 2 /* bytes per sample */ * 2;
	uint32_t nBytesToProcess = nDataSize;

#if defined(DEMO_MODE_WAV_OUT)
	PurrFX::CBufferedFileWriter oWavFile(sOutputPath.data());
	if (!oWavFile.isOpened())
	{
		showErrorMessage("Can't create output file");
		return 1;
	}

	// WAV header

	const int nHdrSize = 44;
	oWavFile.write("RIFF", 4);
	const uint32_t nFileSize = nDataSize + nHdrSize;
	oWavFile.write(&nFileSize, sizeof(nFileSize));
	oWavFile.write("WAVE", 4);
	oWavFile.write("fmt ", 4);
	const uint32_t nFmtChunkSize = 16;
	oWavFile.write(&nFmtChunkSize, sizeof(nFmtChunkSize));
	const uint16_t nFormat = 1; // PCM
	oWavFile.write(&nFormat, sizeof(nFormat));
	uint16_t nChannels = 2; // Stereo
	oWavFile.write(&nChannels, sizeof(nChannels));
	uint32_t nSampleRate_ = nSampleRate;
	oWavFile.write(&nSampleRate_, sizeof(nSampleRate_));
	uint16_t nBitsPerSample = 16;
	uint32_t nBitRate = (nSampleRate * nBitsPerSample * nChannels) / 8;
	oWavFile.write(&nBitRate, sizeof(nBitRate));
	uint16_t nBytesPerSample = (nBitsPerSample * nChannels) / 8;
	oWavFile.write(&nBytesPerSample, sizeof(nBytesPerSample));
	oWavFile.write(&nBitsPerSample, sizeof(nBitsPerSample));
	oWavFile.write("data", 4);
	oWavFile.write(&nDataSize, sizeof(nDataSize));
#endif

	// Run emulation

	while (nBytesToProcess > 0)
	{
		// Prepare buffer
		const uint32_t nBufferSize = 1024;
		char           aBuffer[nBufferSize];

		// Fill buffer
		if (!pNes->render(aBuffer, nBufferSize))
		{
			showErrorMessage("Rendering error");
			return 1;
		}

		uint32_t nSize = nBufferSize;
		if (nSize >= nBytesToProcess)
			nSize  = nBytesToProcess;
		nBytesToProcess -= nSize;

#if defined(DEMO_MODE_WAV_OUT)
		// WAV data
		oWavFile.write(aBuffer, nSize);
#endif
	}

	std::cout << "Success!" << std::endl;
	return 0;
}