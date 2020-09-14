#include "CNesGme.h"
#include "CNesGmeAudioDataProvider.h"
#include "CNesCalculations.h"
#include "DNesConsts.h"
#include "CFile.h"

namespace PurrFX
{
	const nullptr_t NO_ERROR = nullptr;

	CNesGme::CNesGme():
		m_oAudioConverter(16, 2)
	{
	}

	CNesGme::~CNesGme()
	{
		if (m_pEmu != nullptr)
			delete m_pEmu;
	}

	bool CNesGme::prepareEmulator()
	{
		gme_err_t sError = nullptr;

		// Determine file type
		gme_type_t pFileType;
		sError = gme_identify_file("file.nsf", &pFileType);
		if (sError != NO_ERROR || pFileType == nullptr || strcmp(pFileType->system, "Nintendo NES") != 0)
			return false;

		// Create emulator
		Music_Emu* pEmu = pFileType->new_emu();
		if (pEmu == nullptr)
			return false;

		if (m_pEmu != nullptr)
			delete m_pEmu;
		m_pEmu = pEmu;

		// Setup emulator audio
		sError = m_pEmu->set_sample_rate( audioFormat().sampleRate() );
		if (sError != NO_ERROR)
			return false;

		// Setup logging
		Nsf_Emu* pNsfEmu = static_cast<Nsf_Emu*>(m_pEmu);
		Nes_Cpu* pNesCpu = pNsfEmu->cpu_();
		pNesCpu->gme_integrator = this;
		pNsfEmu->apu_()->gme_integrator = this;

		// Other
		pEmu->ignore_silence(true);

		return true;
	}

	bool CNesGme::open(const pathstring& i_sFileName)
	{
		if (!prepareEmulator())
			return false;

		static const size_t nFileSizeLimit = 128*1024; // 128KB should be enough

		bool bSuccess = false;
		CFile oFile(i_sFileName, CFile::Read);
		if (oFile.isOpened())
		{
			size_t nFileSize = oFile.size();
			if (nFileSize >  0 &&
				nFileSize <= nFileSizeLimit)
			{
				uint8_t* pData = new uint8_t[nFileSize];
				oFile.read(pData, nFileSize);
				bSuccess = open(pData, nFileSize);
				delete[] pData;
			}
		}

		return bSuccess;
	}

	bool CNesGme::open(const uint8_t* i_pData, size_t i_nSize)
	{
		if (!prepareEmulator())
			return false;

		gme_err_t sError = m_pEmu->load_mem(i_pData, i_nSize);
		bool bSuccess = (sError == NO_ERROR);
		if (!bSuccess)
		{
			delete m_pEmu;
			m_pEmu = nullptr;
		}
		else
			m_oAudioConverter.reset();
		return bSuccess;
	}

	bool CNesGme::setTrack(int i_nTrack)
	{
		if (m_pEmu == nullptr)
			return false;
		if (i_nTrack < 0 ||
			i_nTrack >= m_pEmu->track_count())
			return false;
		
		gme_err_t sError = m_pEmu->start_track(i_nTrack);
		bool bSuccess = (sError == NO_ERROR);
		if (bSuccess)
			m_oAudioConverter.reset();
		return bSuccess;
	}

	int CNesGme::trackCount() const
	{
		if (m_pEmu == nullptr)
			return 0;
		return m_pEmu->track_count();
	}

	bool CNesGme::render(char* o_pData, size_t i_nDataSize)
	{
		if (m_pEmu == nullptr)
			return false;

		CNesGmeAudioDataProvider oProvider(m_pEmu);
		return m_oAudioConverter.getData(
			o_pData, i_nDataSize,
			audioFormat().bitDepth(),
			audioFormat().channels(),
			&oProvider);
	}

	void CNesGme::onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2)
	{
		if (!nesEventHandlingEnabled())
			return;

		CNesEventCpuInstruction oEvent(i_nAddress, i_nOpcode, i_nArgByte1, i_nArgByte2);
		handleNesEvent(oEvent);
	}

	void CNesGme::onGmeEventCodeLabel(char i_cLabelName)
	{
		if (!nesEventHandlingEnabled())
			return;

		ECodeLabelType eType = ECodeLabelType::Undefined;
		switch (i_cLabelName)
		{
		case 'i':
			eType = ECodeLabelType::InitAddress;
			break;
		case 'p':
			eType = ECodeLabelType::PlayAddress;
			break;
		}
		assert(eType != ECodeLabelType::Undefined);

		CNesEventCodeLabel oEvent(eType);
		handleNesEvent(oEvent);
	}

	void CNesGme::onGmeEventFrameStart(int i_nFrame)
	{
		if (nesEventHandlingEnabled())
		{
			CNesEventFrameStart oEvent(i_nFrame);
			handleNesEvent(oEvent);
		}
		if (usesFrameDataConsumer())
			frameDataConsumer()->startFrame();
	}

	void CNesGme::onGmeEventFrameEnd()
	{
		if (nesEventHandlingEnabled())
		{
			CNesEventFrameEnd oEvent;
			handleNesEvent(oEvent);
		}
		if (usesFrameDataConsumer())
			frameDataConsumer()->endFrame();
	}

	void CNesGme::onGmeEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue)
	{
		if (nesEventHandlingEnabled())
		{
			CNesEventApuRegisterWrite oEvent(i_nRegister, i_nValue);
			handleNesEvent(oEvent);
		}
		if (usesFrameDataConsumer())
		{
			ERegister eRegister = ERegister::Unknown;
			switch(i_nRegister)
			{
				/////////
				// APU //
				/////////

				// Pulse 1
			case 0x4000: eRegister = ERegister::Apu4000; break;
			case 0x4001: eRegister = ERegister::Apu4001; break;
			case 0x4002: eRegister = ERegister::Apu4002; break;
			case 0x4003: eRegister = ERegister::Apu4003; break;
				// Pulse 2
			case 0x4004: eRegister = ERegister::Apu4004; break;
			case 0x4005: eRegister = ERegister::Apu4005; break;
			case 0x4006: eRegister = ERegister::Apu4006; break;
			case 0x4007: eRegister = ERegister::Apu4007; break;
				// Triangle
			case 0x4008: eRegister = ERegister::Apu4008; break;
			case 0x400A: eRegister = ERegister::Apu400A; break;
			case 0x400B: eRegister = ERegister::Apu400B; break;
				// Noise
			case 0x400C: eRegister = ERegister::Apu400C; break;
			case 0x400E: eRegister = ERegister::Apu400E; break;
			case 0x400F: eRegister = ERegister::Apu400F; break;
				// DMC
			case 0x4010: eRegister = ERegister::Apu4010; break;
			case 0x4011: eRegister = ERegister::Apu4011; break;
			case 0x4012: eRegister = ERegister::Apu4012; break;
			case 0x4013: eRegister = ERegister::Apu4013; break;
				// Status
			case 0x4015: eRegister = ERegister::Apu4015; break;

			default:
				assert(false && "Unknown register");
			}
			if (eRegister != ERegister::Unknown)
				frameDataConsumer()->setRegister(eRegister, i_nValue);
		}
	}

	void CNesGme::onGmeDpcmSampleStarted(uint8_t i_nAddress, uint8_t i_nLength)
	{
		if (!usesDpcmDataConsumer())
			return;

		dpcmDataConsumer()->start(i_nAddress, i_nLength);

		uint16_t nSampleBytes   = CNesCalculations::dpcmSampleLengthUnpack(i_nLength);
		uint16_t nSampleAddress = CNesCalculations::dpcmSampleAddressUnpack(i_nAddress);

		Nsf_Emu* pNsfEmu = static_cast<Nsf_Emu*>(m_pEmu);
		for (uint16_t i = 0; i < nSampleBytes; i++)
			dpcmDataConsumer()->addByte( pNsfEmu->cpu_read_(nSampleAddress+i) );
		
		dpcmDataConsumer()->end();
	}

	bool CNesGme::gmeGetFrameCode(std::vector<uint8_t>& o_rCode)
	{
		auto* pDataSource = frameDataProducer();
		if (pDataSource == nullptr)
			return false;
		if (!pDataSource->available())
			return false;

		CFrameData oData = pDataSource->get();
		CFrameDataProcessor oDataProcessor(oData);
		oDataProcessor.generateAssemblyCode(o_rCode);

		pDataSource->next();
		return true;
	}

	bool CNesGme::gmeActivateDpcmSample(uint8_t i_nAddress, uint8_t i_nLength)
	{
		if (!usesDpcmDataProvider())
			return false;
		
		const CDpcmSample* pSample = dpcmDataProvider()->getSample();
		if (pSample == nullptr)
			pSample = dpcmDataProvider()->getSample(i_nAddress, i_nLength);

		if (pSample == nullptr)
			return false;

		Nsf_Emu* pNsfEmu = static_cast<Nsf_Emu*>(m_pEmu);
		Nes_Cpu* pNesCpu = pNsfEmu->cpu_();
		for (uint16_t nByteIndex = 0; nByteIndex < pSample->size(); nByteIndex++)
			pNesCpu->memory_write(NesConsts::dpcmSampleAddressMin+nByteIndex, pSample->get(nByteIndex));
		return true;
	}

}