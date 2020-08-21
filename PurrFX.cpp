// PurrFX demo

#include <iostream>
#include <string>

#include "purrfx/CNesGme.h"
#include "purrfx/CAudioDataConsumerWavWriter.h"
#include "purrfx/CAudioDataConsumerDummy.h"
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

	std::string    sInputFile  = "Gimmick!.nsf";
	std::string    sOutputFile = "out";
	const int      nTrack      = 6;     // track index
	const uint32_t nTime       = 60;    // time in seconds
	const int      nSampleRate = 44100; // sound quality

	//////////////////
	// Preparations //
	//////////////////

#if defined (DEMO_MODE_WAV_OUT)
	sOutputFile += ".wav";
#elif defined (DEMO_MODE_LOG)
	sOutputFile += ".log";
#endif
	std::string sOutputPath = outputPath(sOutputFile);
	
	///////////
	// Setup //
	///////////

	PurrFX::CNesGme oNes;
	PurrFX::CNes* pNes = &oNes;

#if defined (DEMO_MODE_WAV_OUT)
	PurrFX::CWavWriter oWavWriter( sOutputPath.data(), nTime );
	pNes->setAudioDataConsumer(&oWavWriter);
#elif defined (DEMO_MODE_LOG)
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