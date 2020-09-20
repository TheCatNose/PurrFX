#pragma once
// Class for converting sound frequency to piano note and vice versa

#include <cassert>
#include <cmath>
#include "DClass.h"

namespace PurrFX
{
	class CNote
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNote)
	public:
		CNote(double i_nFrequence);

		int    octave() const;
		int    note() const;
		double offset() const;

		double frequence() const;

	private:
		int     m_nOctave;
		int     m_nNote;
		double  m_nOffset;

		static const int KeysInOctave = 12;
	};
}
