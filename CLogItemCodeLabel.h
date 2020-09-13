#pragma once
// Log item for code label

#include <cassert>
#include "DClass.h"
#include "CLogItem.h"
#include "ECodeLabelType.h"

namespace PurrFX
{
	class CLogItemCodeLabel: public CLogItem
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CLogItemCodeLabel)
	public:
		CLogItemCodeLabel(ECodeLabelType i_eType);

		ECodeLabelType labelType() const;

		// CLogItem implementation
		virtual ELogItemType type() const;

	private:
		ECodeLabelType m_eType;
	};
}