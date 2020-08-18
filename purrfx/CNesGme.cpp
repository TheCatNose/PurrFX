#include "CNesGme.h"

namespace PurrFX
{
	const nullptr_t NO_ERROR = nullptr;

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
		sError = m_pEmu->set_sample_rate( soundSampleRate() );
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
		return (sError == NO_ERROR);
	}

	bool CNesGme::render(char* o_pData, size_t i_nDataSize)
	{
		if (m_pEmu == nullptr)
			return false;

		auto*  pData = reinterpret_cast<Music_Emu::sample_t*>(o_pData);
		size_t nSize = i_nDataSize / sizeof(Music_Emu::sample_t);

		gme_err_t sError = m_pEmu->play(nSize, pData);
		return (sError == NO_ERROR);
	}

	void CNesGme::onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2)
	{
		if (!logEnabled())
			return;

		CNesLogItemCpuInstruction oLogItem(i_nAddress, i_nOpcode, i_nArgByte1, i_nArgByte2);
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventCodeLabel(char i_cLabelName)
	{
		if (!logEnabled())
			return;

		ENesCodeLabelType eType = ENesCodeLabelType::Undefined;
		switch (i_cLabelName)
		{
		case 'i':
			eType = ENesCodeLabelType::InitAddress;
			break;
		case 'p':
			eType = ENesCodeLabelType::PlayAddress;
			break;
		}
		assert(eType != ENesCodeLabelType::Undefined);

		CNesLogItemCodeLabel oLogItem(eType);
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventFrameStart(int i_nFrame)
	{
		if (!logEnabled())
			return;

		CNesLogItemFrameStart oLogItem(i_nFrame);
		logAddItem(oLogItem);
	}

	void CNesGme::onGmeEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue)
	{
		if (!logEnabled())
			return;

		CNesLogItemApuRegisterWrite oLogItem(i_nRegister, i_nValue);
		logAddItem(oLogItem);
	}

}