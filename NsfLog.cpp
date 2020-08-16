#include <iostream>
#include "purrfx/CNesGme.h"
#include "purrfx/CNesLogFileWriter.h"
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
	const char* sOutputFile = "out.log";
	const int   nTrack      = 6;     // track index
	const int   nTime       = 60;    // time in seconds
	const int   nSampleRate = 44100; // sound quality
	
	/////////////////////
	// Setup emulation //
	/////////////////////

	std::string sOutputPath = CDataPath::outputFile(sOutputFile);
	
	PurrFX::CNesGme oNes;
	PurrFX::CNesLogFileWriter oLogWriter( sOutputPath.data() );
	oNes.setLogDataConsumer(&oLogWriter);

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
	// Log output //
	////////////////

	// Run emulation to collect log data

	const uint32_t nDataSize       = nTime * nSampleRate /* stereo */ * 2 /* bytes per sample */ * 2;
	uint32_t       nBytesToProcess = nDataSize;

	while (nBytesToProcess > 0)
	{
		// Prepare buffer
		const uint32_t nBufferSize = 1024;
		char           aBuffer[nBufferSize];

		// Fill buffer
		if (!oNes.render(aBuffer, nBufferSize))
		{
			showErrorMessage("Rendering error");
			return 1;
		}

		uint32_t nSize = nBufferSize;
		if (nSize >= nBytesToProcess)
			nSize  = nBytesToProcess;
		nBytesToProcess -= nSize;
	}

	std::cout << "Success!" << std::endl;
	return 0;
}