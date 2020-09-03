// PurrFX demo

#include <iostream>
#include <string>
#include <filesystem>
#include "../PurrFX.h"
#include "../CFrameDataFileWriter.h"
#include "../CFrameDataFileReader.h"
#include "../CDpcmDataFileWriter.h"
#include "../CDpcmDataProviderStd.h"
#include "../CDpcmFile.h"
#include "../DPath.h"

void showErrorMessage(const char* i_sMessage)
{
	if (i_sMessage != nullptr)
		std::cout << "Error: " << i_sMessage << std::endl;
}
PurrFX::pathstring inputPath (const PurrFX::pathstring& i_sFileName) { return PurrFX::pathstring(PATHSTR("../data/in/" )) + i_sFileName; }
PurrFX::pathstring outputPath(const PurrFX::pathstring& i_sFileName) { return PurrFX::pathstring(PATHSTR("../data/out/")) + i_sFileName; }

void loadDpcmSamples(PurrFX::CDpcmDataProviderStd& i_rProdiver)
{
    for (const auto& rEntry: std::filesystem::directory_iterator("../data/in/"))
	{
		PurrFX::pathstring sExt = 
#ifdef _WIN32
			rEntry.path().extension().generic_wstring();
#else
			rEntry.path().extension().generic_string();
#endif
		if (!(sExt == PATHSTR(".raw") || sExt == PATHSTR(".dmc") ))
			continue;

        PurrFX::pathstring sPath = PATHSTR("../data/in/") + 
#ifdef _WIN32
			rEntry.path().filename().generic_wstring();
#else
			rEntry.path().filename().generic_string();
#endif
		auto* pSample = PurrFX::CDpcmFile::load(sPath);
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

	PurrFX::pathstring sInputFile  = PATHSTR("Gimmick!.nsf");
	PurrFX::pathstring sOutputFile = PATHSTR("out");
	const int          nTrack      = 6;     // track index
	const uint32_t     nTime       = 60;    // time in seconds

	// Sound quality
	PurrFX::CAudioFormat oAudioFormat(44100);

	//////////////////
	// Preparations //
	//////////////////

#if   DEMO_MODE == DEMO_MODE_WAV | DEMO_MODE == DEMO_MODE_FD_PLAY
	sOutputFile += PATHSTR(".wav");
#elif DEMO_MODE == DEMO_MODE_LOG
	sOutputFile += PATHSTR(".log");
#elif DEMO_MODE == DEMO_MODE_FD_CAPTURE
	sOutputFile += PATHSTR(".fd");
#endif

#if DEMO_MODE == DEMO_MODE_FD_PLAY
	// You must use frame data file as input file
	assert(sInputFile.substr(sInputFile.size()-3, 3) == PATHSTR(".fd"));
#endif


	PurrFX::pathstring sOutputPath = outputPath(sOutputFile);
	PurrFX::pathstring sInputPath  = inputPath(sInputFile);
	
	///////////
	// Setup //
	///////////

	PurrFX::CNesPtr oNes(PurrFX::ENesType::GameMusicEmu);

#if   DEMO_MODE == DEMO_MODE_WAV | DEMO_MODE == DEMO_MODE_FD_PLAY
	PurrFX::CWavWriter oWavWriter( sOutputPath, nTime );
	oNes->setAudioDataConsumer(&oWavWriter);
#endif
#if DEMO_MODE == DEMO_MODE_LOG
	oNes->logItemTypeDisable(PurrFX::ELogItemType::CpuInstruction);
	oNes->logItemTypeDisable(PurrFX::ELogItemType::CodeLabel);
	oNes->logItemTypeDisable(PurrFX::ELogItemType::FrameEnd);
	PurrFX::CLogFileWriter oLogWriter( sOutputPath );
	oNes->setLogDataConsumer(&oLogWriter);
#endif
#if DEMO_MODE == DEMO_MODE_FD_CAPTURE
	PurrFX::CFrameDataFileWriter oFdWriter( sOutputPath );
	oNes->setFrameDataConsumer(&oFdWriter);
#endif
#if DEMO_MODE == DEMO_MODE_FD_PLAY
	PurrFX::CFrameDataFileReader oFdReader( sInputPath );
	oNes->setFrameDataProducer(&oFdReader);

	PurrFX::CDpcmDataProviderStd oDpcmProvider(true);
	loadDpcmSamples(oDpcmProvider);
	oNes->setDpcmDataProvider(&oDpcmProvider);
#endif
#if DEMO_MODE == DEMO_MODE_DPCM_GRAB
	PurrFX::CDpcmDataFileWriter oDpcmWriter(PATHSTR("../data/out/"), PurrFX::EDpcmFileType::Dmc);
	oNes->setDpcmDataConsumer(&oDpcmWriter);
#endif


	oNes->setAudioFormat( oAudioFormat );
#if DEMO_MODE == DEMO_MODE_FD_PLAY
	if (!oNes->open())
#else
	
	if (!oNes->open(sInputPath))
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