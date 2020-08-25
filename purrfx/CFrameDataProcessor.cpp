#include "CFrameDataProcessor.h"

PurrFX::CFrameDataProcessor::CFrameDataProcessor(const CFrameData& i_rData):
	m_rData(i_rData)
{
}

void PurrFX::CFrameDataProcessor::generateAssemblyCode(std::vector<uint8_t>& o_rCode)
{
	o_rCode.reserve(256);

	bool bPlayDMC = 
		m_rData.isSet(ERegister::Apu4010) ||
		m_rData.isSet(ERegister::Apu4011) ||
		m_rData.isSet(ERegister::Apu4012) ||
		m_rData.isSet(ERegister::Apu4013) ;

	for (int i = 0; i < RegisterCount; i++)
	{
		ERegister eRegister = ERegister(i);
		if (!m_rData.isSet(eRegister))
			continue;

		uint16_t aRegisters[RegisterCount] =
		{
			/////////
			// APU //
			/////////
			0x4000, 0x4001, 0x4002, 0x4003, // Pulse 1
			0x4004, 0x4005, 0x4006, 0x4007, // Pulse 2
			0x4008, 0x400A, 0x400B,         // Triangle
			0x400C, 0x400E, 0x400F,         // Noise
			0x4010, 0x4011, 0x4012, 0x4013, // DMC
			0x4015,                         // Status
		};
		uint16_t nRegister  = aRegisters[i];
		uint8_t  nRegisterL = uint8_t( nRegister &  0xFF );
		uint8_t  nRegisterH = uint8_t( nRegister >> 8   );

		const uint8_t nValue = m_rData.get(eRegister);
		if (eRegister == ERegister::Apu4015 && bPlayDMC)
			continue;

		o_rCode.push_back( 0xA9 ); // (LDA) A = Value
		o_rCode.push_back( nValue );
		o_rCode.push_back( 0x8D ); // (STA) $X = A
		o_rCode.push_back( nRegisterL );
		o_rCode.push_back( nRegisterH );
	}

	if (bPlayDMC)
	{
		// Special case for DMC:
		// 4015 <- 0x0F
		// 4015 <- 0x1F
		const size_t nDmcCodeSize = 10;
		uint8_t      aDmcCode[nDmcCodeSize] = {0xA9, 0x0F, 0x8D, 0x15, 0x40, 0xA9, 0x1F, 0x8D, 0x15, 0x40};
		for (size_t i = 0; i < nDmcCodeSize; i++)
			o_rCode.push_back(aDmcCode[i]);
	}

	o_rCode.push_back( 0x60 ); // (RTS) Return from the function
}
