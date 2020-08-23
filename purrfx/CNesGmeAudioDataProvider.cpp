#include "CNesGmeAudioDataProvider.h"


PurrFX::CNesGmeAudioDataProvider::CNesGmeAudioDataProvider(Music_Emu* i_pEmu):
	m_pEmu(i_pEmu)
{}

bool PurrFX::CNesGmeAudioDataProvider::getData(char* o_pData, size_t i_nDataSize)
{
	auto*  pData = reinterpret_cast<Music_Emu::sample_t*>(o_pData);
	size_t nSize = i_nDataSize / sizeof(Music_Emu::sample_t);

	const nullptr_t NO_ERROR = nullptr;
	gme_err_t sError = m_pEmu->play(nSize, pData);
	return (sError == NO_ERROR);
}
