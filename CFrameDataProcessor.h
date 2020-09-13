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
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CFrameDataProcessor)
		CLASS_MAKE_NON_COPYABLE(CFrameDataProcessor)
	public:
		CFrameDataProcessor(const CFrameData& i_rData);
		void generateAssemblyCode(std::vector<uint8_t>& o_rCode);

	private:
		const CFrameData& m_rData;
	};
}