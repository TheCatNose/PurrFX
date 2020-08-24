#include "CFrameDataConsumer.h"

PurrFX::CFrameDataConsumer::~CFrameDataConsumer()
{
}

void PurrFX::CFrameDataConsumer::startFrame()
{
	m_bFrameStarted = true;
}

void PurrFX::CFrameDataConsumer::setRegister(ERegister i_eRegister, uint8_t i_nValue)
{
	if (!m_bFrameStarted)
		return;

	m_oData.set(i_eRegister, i_nValue);
}

void PurrFX::CFrameDataConsumer::endFrame()
{
	if (!m_bFrameStarted)
		return;
	m_bFrameStarted = false;

	onFrameDataReady(m_oData);
	m_oData.reset();
}
