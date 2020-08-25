// PurrFX demo

#include <iostream>
#include <string>
#include "purrfx/PurrFX.h"
#include "purrfx/CFrameDataFileWriter.h"
#include "purrfx/CFrameDataFileReader.h"

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
#define DEMO_MODE_FD_PLAY    3

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

	// Additional settings
#if DEMO_MODE == DEMO_MODE_FD_PLAY
	std::string sInputFD = "in.fd";
#endif

	//////////////////
	// Preparations //
	//////////////////

#if   DEMO_MODE == DEMO_MODE_WAV | DEMO_MODE == DEMO_MODE_FD_PLAY
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

	PurrFX::CNesPtr oNes(PurrFX::ENesType::GameMusicEmu);

#if   DEMO_MODE == DEMO_MODE_WAV | DEMO_MODE == DEMO_MODE_FD_PLAY
	PurrFX::CWavWriter oWavWriter( sOutputPath.data(), nTime );
	oNes->setAudioDataConsumer(&oWavWriter);
#endif
#if DEMO_MODE == DEMO_MODE_LOG
	oNes->logItemTypeDisable(PurrFX::ELogItemType::CpuInstruction);
	oNes->logItemTypeDisable(PurrFX::ELogItemType::CodeLabel);
	oNes->logItemTypeDisable(PurrFX::ELogItemType::FrameEnd);
	PurrFX::CLogFileWriter oLogWriter( sOutputPath.data() );
	oNes->setLogDataConsumer(&oLogWriter);
#endif
#if DEMO_MODE == DEMO_MODE_FD_CAPTURE
	PurrFX::CFrameDataFileWriter oFdWriter( sOutputPath.data() );
	oNes->setFrameDataConsumer(&oFdWriter);
#endif
#if DEMO_MODE == DEMO_MODE_FD_PLAY
	std::string sFdPath = inputPath(sInputFD);
	PurrFX::CFrameDataFileReader oFdReader( sFdPath.data() );
	oNes->setFrameDataProducer(&oFdReader);
#endif
	oNes->setAudioFormat( oAudioFormat );
	std::string sInputPath = inputPath(sInputFile);
	if (!oNes->open( sInputPath.data() ))
	{
		showErrorMessage("Can't open file");
		return 1;
	}
	if (!oNes->setTrack(nTrack))
	{
		showErrorMessage("Can't set track");
		return 1;
	}

	PurrFX::CAudioDataConsumerDummy oDummy(nTime);
	if (!oNes->usesAudioDataConsumer())
		 oNes->setAudioDataConsumer(&oDummy);

	////////////
	// Render //
	////////////

	if (!oNes->render())
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