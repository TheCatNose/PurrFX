// PurrFX demo

#include <iostream>
#include <string>
#include <filesystem>
#include "purrfx/PurrFX.h"
#include "purrfx/CFrameDataFileWriter.h"
#include "purrfx/CFrameDataFileReader.h"
#include "purrfx/CDpcmDataFileWriter.h"
#include "purrfx/CDpcmDataProviderStd.h"
#include "purrfx/CDpcmFile.h"

void showErrorMessage(const char* i_sMessage)
{
	if (i_sMessage != nullptr)
		std::cout << "Error: " << i_sMessage << std::endl;
}
std::string inputPath (const std::string& i_sFileName) { return std::string("data/in/") + i_sFileName; }
std::string outputPath(const std::string& i_sFileName) { return std::string("data/out/") + i_sFileName; }

void loadDpcmSamples(PurrFX::CDpcmDataProviderStd& i_rProdiver)
{
    for (const auto& rEntry: std::filesystem::directory_iterator("./data/in/"))
	{
		std::string sExt = rEntry.path().extension().generic_string();
		if (!(sExt == ".raw" || sExt == ".dmc" ))
			continue;

        std::string sPath = "./data/in/" + rEntry.path().filename().generic_string();
		auto* pSample = PurrFX::CDpcmFile::load(sPath.data());
		if (pSample != nullptr)
			i_rProdiver.add(pSample);
	}
}

#define	DEMO_MODE_WAV        0
#define	DEMO_MODE_LOG        1
#define DEMO_MODE_FD_CAPTURE 2
#define DEMO_MODE_FD_PLAY    3
#define DEMO_MODE_DPCM_GRAB  4

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

#if   DEMO_MODE == DEMO_MODE_WAV | DEMO_MODE == DEMO_MODE_FD_PLAY
	sOutputFile += ".wav";
#elif DEMO_MODE == DEMO_MODE_LOG
	sOutputFile += ".log";
#elif DEMO_MODE == DEMO_MODE_FD_CAPTURE
	sOutputFile += ".fd";
#endif

#if DEMO_MODE == DEMO_MODE_FD_PLAY
	// You must use frame data file as input file
	assert(sInputFile.substr(sInputFile.size()-3, 3) == ".fd");
#endif


	std::string sOutputPath = outputPath(sOutputFile);
	std::string sInputPath  = inputPath(sInputFile);
	
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
	PurrFX::CFrameDataFileReader oFdReader( sInputPath.data() );
	oNes->setFrameDataProducer(&oFdReader);

	PurrFX::CDpcmDataProviderStd oDpcmProvider(true);
	loadDpcmSamples(oDpcmProvider);
	oNes->setDpcmDataProvider(&oDpcmProvider);
#endif
#if DEMO_MODE == DEMO_MODE_DPCM_GRAB
	PurrFX::CDpcmDataFileWriter oDpcmWriter("./data/out/", PurrFX::EDpcmFileType::Dmc);
	oNes->setDpcmDataConsumer(&oDpcmWriter);
#endif


	oNes->setAudioFormat( oAudioFormat );
#if DEMO_MODE == DEMO_MODE_FD_PLAY
	if (!oNes->open())
#else
	
	if (!oNes->open( sInputPath.data() ))
#endif
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