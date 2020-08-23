#include "CNesGme.h"
#include "CNesGmeAudioDataProvider.h"

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
		if (sError != NO_ERROR || pFileType == nullptr || pFileType->system != "Nintendo NES")
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
		pNesCpu->events_receiver = this;
		pNsfEmu->apu_()->events_receiver = this;

		return true;
	}

	bool CNesGme::open(const char* i_sFileName)
	{
		if (!prepareEmulator())
			return false;

		gme_err_t sError = m_pEmu->load_file(i_sFileName);
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

	bool CNesGme::open(const char* i_pData, size_t i_nSize)
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
		if (!logEnabled())
			return;

		CLogItemCpuInstruction oLogItem(i_nAddress, i_nOpcode, i_nArgByte1, i_nArgByte2);
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventCodeLabel(char i_cLabelName)
	{
		if (!logEnabled())
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

		CLogItemCodeLabel oLogItem(eType);
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventFrameStart(int i_nFrame)
	{
		if (!logEnabled())
			return;

		CLogItemFrameStart oLogItem(i_nFrame);
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventFrameEnd()
	{
		if (!logEnabled())
			return;

		CLogItemFrameEnd oLogItem;
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue)
	{
		if (!logEnabled())
			return;

		CLogItemApuRegisterWrite oLogItem(i_nRegister, i_nValue);
		logAddItem(oLogItem);
	}

}