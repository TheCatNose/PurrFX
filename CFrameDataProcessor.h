#pragma once
// Does some useful actions with frame data:
// * Generates assembly code

#include <vector>
#include "DClass.h"
#include "CFrameData.h"

namespace PurrFX
{
	class CFrameDataProcessor
	{
	public:
		CFrameDataProcessor(const CFrameData& i_rData);
		void generateAssemblyCode(std::vector<uint8_t>& o_rCode);

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFrameDataProcessor)
		CLASS_MAKE_NON_COPYABLE(CFrameDataProcessor)
	private:
		const CFrameData& m_rData;
	};
}