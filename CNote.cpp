#include "CNote.h"

PurrFX::CNote::CNote()
{
}

PurrFX::CNote::CNote(double i_nFrequency)
{
	assert(i_nFrequency > 0);
	double nPianoKeyNumber = 12.0*log2(i_nFrequency/440.0) + 49.0;
	double nNoteIndex = nPianoKeyNumber + 8;

	if (nNoteIndex < 0) // can't be less than C0
		nNoteIndex = 0; 

	m_nOctave = int(nNoteIndex / KeysInOctave);
	m_nNote   = int(nNoteIndex - m_nOctave*KeysInOctave);
	m_nOffset = nNoteIndex - int(nNoteIndex);

	if (m_nOffset > 0.5)
	{
		m_nOffset-=1;
		m_nNote++;
		if (m_nNote == KeysInOctave)
		{
			m_nNote = 0;
			m_nOctave++;
		}
	}
}

PurrFX::CNote::CNote(int i_nOctave, int i_nNote, double i_nOffset)
{
	assert(i_nOctave >= -1);
	assert(i_nNote >= 0 && i_nNote < KeysInOctave);
	assert(abs(i_nOffset) <= 0.5);

	m_nOctave = i_nOctave;
	m_nNote   = i_nNote;
	m_nOffset = i_nOffset;
}

int PurrFX::CNote::octave() const
{
	return m_nOctave;
}

int PurrFX::CNote::note() const
{
	return m_nNote;
}

double PurrFX::CNote::offset() const
{
	return m_nOffset;
}

double PurrFX::CNote::frequency() const
{
	double nKeyNumber = double(m_nOctave)*KeysInOctave + m_nNote + m_nOffset;
	return pow(2.0, (nKeyNumber-49.0)/12.0)*440.0;
}
