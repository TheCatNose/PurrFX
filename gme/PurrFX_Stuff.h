#pragma once

// Special stuff for PurrFX integration

#include <cstdint>

class CGmeEventsReceiver
{
public:
	virtual void onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2) = 0;
	virtual void onGmeEventCodeLabel(char i_cLabelName) = 0;
	virtual void onGmeEventFrameStart(int i_nFrame) = 0;
	virtual void onGmeEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue) = 0;
};