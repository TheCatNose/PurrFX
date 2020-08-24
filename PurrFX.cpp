// PurrFX demo

#include <iostream>
#include <string>
#include "purrfx/PurrFX.h"
#include "purrfx/CFrameDataFileWriter.h"

void showErrorMessage(const char* i_sMessage)
{
	if (i_sMessage != nullptr)
		std::cout << "Error: " << i_sMessage << std::endl;
}
std::string inputPath (const std::string& i_sFileName) { return std::string("data/in/") + i_sFileName; }
std::string outputPath(const std::string& i_sFileName) { return std::string("data/out/") + i_sFileName; }

#define	DEMO_MODE_WAV        0
#define	DEMO_MODE_LOG        1
#define DEMO_MODE_FD_CAPTURE 2

// Choose demo mode here:
#define DEMO_MODE	DEMO_MODE_WAV

int main()
{
	//////////////
	// Settings //
	//////////////

	std::string    sInputFile  = "Gimmick!.nsf";
	std::string    sOutputFile = "out";
	const int      nTrack      = 6;     // track index
	const uint32_t nTime       = 60;    // time in seconds

	// Sound quality
	PurrFX::CAudioFormat oAudioFormat(44100);

	//////////////////
	// Preparations //
	//////////////////

#if   DEMO_MODE == DEMO_MODE_WAV
	sOutputFile += ".wav";
#elif DEMO_MODE == DEMO_MODE_LOG
	sOutputFile += ".log";
#elif DEMO_MODE == DEMO_MODE_FD_CAPTURE
	sOutputFile += ".fd";
#endif
	std::string sOutputPath = outputPath(sOutputFile);
	
	///////////
	// Setup //
	///////////

	PurrFX::CNesGme oNes;
	PurrFX::CNes* pNes = &oNes;

#if   DEMO_MODE == DEMO_MODE_WAV
	PurrFX::CWavWriter oWavWriter( sOutputPath.data(), nTime );
	pNes->setAudioDataConsumer(&oWavWriter);
#elif DEMO_MODE == DEMO_MODE_LOG
	pNes->logItemTypeDisable(PurrFX::ELogItemType::CpuInstruction);
	pNes->logItemTypeDisable(PurrFX::ELogItemType::CodeLabel);
	pNes->logItemTypeDisable(PurrFX::ELogItemType::FrameEnd);
	PurrFX::CLogFileWriter oLogWriter( sOutputPath.data() );
	pNes->setLogDataConsumer(&oLogWriter);
#elif DEMO_MODE == DEMO_MODE_FD_CAPTURE
	PurrFX::CFrameDataFileWriter oFdWriter( sOutputPath.data() );
	pNes->setFrameDataConsumer(&oFdWriter);
#endif
	pNes->setAudioFormat( oAudioFormat );
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

	PurrFX::CAudioDataConsumerDummy oDummy(nTime);
	if (!pNes->usesAudioDataConsumer())
		 pNes->setAudioDataConsumer(&oDummy);

	////////////
	// Render //
	////////////

	if (!pNes->render())
	{
		showErrorMessage("Audio rendering failure");
		return 1;
	}

	/////////
	// End //
	/////////

	std::cout << "Success!" << std::endl;
	return 0;
}