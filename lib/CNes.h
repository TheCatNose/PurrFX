#pragma once

// Base class for all NES emulation code wrappers

namespace PurrFX
{

	class CNes
	{
	public:
		virtual ~CNes();

		virtual bool open(const char* i_sName) = 0;
		virtual bool setTrack(int i_nTrack) = 0;
		virtual bool render(char* o_pData, size_t i_nDataSize) = 0;

		bool setSoundOptions(int i_nSampleRate);
		int  soundSampleRate();

	private:
		int m_nSoundSampleRate = 44100;
	};

}
