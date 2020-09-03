#pragma once
// NSF template for creating in-memory files

#include <cstdint>
#include <vector>

namespace PurrFX
{
	class CNsfTemplate
	{
	public:
		static void create(std::vector<uint8_t>& o_rData);

	private:
		static uint8_t low (uint16_t i_nValue);
		static uint8_t high(uint16_t i_nValue);
	};
}