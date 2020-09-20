#pragma once
// Byte order detection

#include <cstdint>
#include "EByteOrder.h"

namespace PurrFX
{
	class CByteOrder
	{
	public:
		static EByteOrder get();
	};
}