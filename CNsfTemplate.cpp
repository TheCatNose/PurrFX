#include "CNsfTemplate.h"

void PurrFX::CNsfTemplate::create(std::vector<uint8_t>& o_rData)
{
	///////////////
	// Init code //
	///////////////

	const uint8_t aInitCode[] = {
	//	LDA   value STA   low   high
		0xA9, 0x30, 0x8D, 0x00, 0x40, // $4000 <- 30
		0xA9, 0x00, 0x8D, 0x01, 0x40, // $4001 <- 00
		0xA9, 0x00, 0x8D, 0x02, 0x40, // $4002 <- 00
		0xA9, 0x00, 0x8D, 0x03, 0x40, // $4003 <- 00
		0xA9, 0x30, 0x8D, 0x04, 0x40, // $4004 <- 30
		0xA9, 0x00, 0x8D, 0x05, 0x40, // $4005 <- 00
		0xA9, 0x00, 0x8D, 0x06, 0x40, // $4006 <- 00
		0xA9, 0x00, 0x8D, 0x07, 0x40, // $4007 <- 00
		0xA9, 0x00, 0x8D, 0x08, 0x40, // $4008 <- 00
		0xA9, 0x00, 0x8D, 0x0A, 0x40, // $400A <- 00
		0xA9, 0x00, 0x8D, 0x0B, 0x40, // $400B <- 00
		0xA9, 0x30, 0x8D, 0x0C, 0x40, // $400C <- 30
		0xA9, 0x00, 0x8D, 0x0E, 0x40, // $400E <- 00
		0xA9, 0x00, 0x8D, 0x0F, 0x40, // $400F <- 00
		0xA9, 0x00, 0x8D, 0x10, 0x40, // $4010 <- 00
		0xA9, 0x00, 0x8D, 0x11, 0x40, // $4011 <- 00
		0xA9, 0x00, 0x8D, 0x12, 0x40, // $4012 <- 00
		0xA9, 0x00, 0x8D, 0x13, 0x40, // $4013 <- 00
		0xA9, 0x1F, 0x8D, 0x15, 0x40, // $4015 <- 1F
		0x60,                         // RST (return to the driver)
	};
	const size_t nInitCodeSize = sizeof(aInitCode);

	///////////////
	// Play code //
	///////////////

	const uint8_t aPlayCode[] = {
		0x4C, // JMP to $6000
		0x00,
		0x60,
	};
	const size_t nPlayCodeSize = sizeof(aPlayCode);

	////////////
	// Header //
	////////////

	const size_t nLoadAddress = 0x8000;
	const size_t nInitAddress = nLoadAddress;
	const size_t nPlayAddress = nInitAddress + nInitCodeSize;

	const uint8_t aHeader[] = {
		// HEADER
		'N', 'E', 'S', 'M', 0x1A,                                                            // File format
		0x01,                                                                                // NSF version
		0xFF,                                                                                // Songs count
		0x01,                                                                                // Starting song
		low(nLoadAddress), high(nLoadAddress),                                               // Load address
		low(nInitAddress), high(nInitAddress),                                               // Init address
		low(nPlayAddress), high(nPlayAddress),                                               // Play address
		'P','u','r','r','F','X',' ','N','S','F',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // Song name
		'C','a','t','N','o','s','e',0  ,0  ,0  ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // Artist
		'C','a','t','N','o','s','e',0  ,0  ,0  ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // Copyright
		0x1A, 0x41,                                                                          // Play speed, NTSC (recommended value)
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                      // Bankswitch init values
		0x1D, 0x4E,                                                                          // Play speed, PAL  (suggested value)
		0x00,                                                                                // PAL/NTSC mode (NTSC)
		0x00,                                                                                // Extra sound chip support (none)
		0x00, 0x00, 0x00, 0x00,                                                              // Unused
	};
	const size_t nHeaderSize = sizeof(aHeader);
	static_assert(nHeaderSize == 0x80, "Wrong NSF header size");

	/////////////////////////
	// Assembling NSF file //
	/////////////////////////

	const size_t nNsfSize = nHeaderSize + nInitCodeSize + nPlayCodeSize;
	o_rData.reserve(nNsfSize);

	for (size_t i = 0; i < nHeaderSize; i++)
		o_rData.push_back( aHeader[i]);
	for (size_t i = 0; i < nInitCodeSize; i++)
		o_rData.push_back( aInitCode[i]);
	for (size_t i = 0; i < nPlayCodeSize; i++)
		o_rData.push_back( aPlayCode[i]);
}

uint8_t PurrFX::CNsfTemplate::low(uint16_t i_nValue)
{
	return uint8_t(  i_nValue & 0x00FF );
}

uint8_t PurrFX::CNsfTemplate::high(uint16_t i_nValue)
{
	return uint8_t( (i_nValue & 0xFF00) >> 8 );
}
