#pragma once

// Special stuff for PurrFX integration

#include <cstdint>
#include <vector>

class CGmeIntegrator
{
public:
	virtual void onGmeEventCpuInstruction(uint16_t i_nAddress, uint8_t i_nOpcode, uint8_t i_nArgByte1, uint8_t i_nArgByte2) = 0;
	virtual void onGmeEventCodeLabel(char i_cLabelName) = 0;
	virtual void onGmeEventFrameStart(int i_nFrame) = 0;
	virtual void onGmeEventFrameEnd() = 0;
	virtual void onGmeEventApuRegisterWrite(uint16_t i_nRegister, uint8_t i_nValue) = 0;
	virtual void onGmeDpcmSampleStarted(uint8_t i_nAddress, uint8_t i_nLength) = 0;

	virtual bool gmeGetFrameCode(std::vector<uint8_t>& o_rCode) = 0;
};