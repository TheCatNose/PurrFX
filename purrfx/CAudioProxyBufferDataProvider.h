#pragma once
// Data source for CAudioProxyBuffer

namespace PurrFX
{
	class CAudioProxyBufferDataProvider
	{
	public:
		virtual bool getData(char* o_pData, size_t i_nSize) = 0;
	};
}