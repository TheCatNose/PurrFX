#pragma once
// Class for converting sound frequency to piano note and vice versa

#include <cassert>
#include <cmath>
#include "DClass.h"

namespace PurrFX
{
	class CNote
	{
	public:
		CNote();
		CNote(double i_nFrequency);
		CNote(int i_nOctave, int i_nNote, double i_nOffset = 0);

		int    octave() const;
		int    note() const;
		double offset() const;

		double frequency() const;

	private:
		int     m_nOctave = 0;
		int     m_nNote   = 0;
		double  m_nOffset = 0.0;

		static const int KeysInOctave = 12;
	};
}
