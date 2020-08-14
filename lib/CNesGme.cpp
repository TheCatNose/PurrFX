#include "CNesGme.h"

namespace PurrFX
{
	const nullptr_t NO_ERROR = nullptr;

	CNesGme::~CNesGme()
	{
		if (m_pEmu != nullptr)
			delete m_pEmu;
	}

	bool CNesGme::open(const char* i_sFileName)
	{
		gme_err_t sError = nullptr;

		// Determine file type
		gme_type_t pFileType;
		sError = gme_identify_file(i_sFileName, &pFileType);
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
		Nes_Cpu* pNesCpu = static_cast<Nsf_Emu*>(m_pEmu)->cpu_();
		pNesCpu->events_receiver = this;

		// Load music file
		sError = m_pEmu->load_file(i_sFileName);
		return (sError == NO_ERROR);
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

	void CNesGme::onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArg1, uint8_t i_nArg2)
	{
		// TODO: Print or store somewhere
	}

}