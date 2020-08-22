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
	public:
		CLogItemCodeLabel(ECodeLabelType i_eType);

		ECodeLabelType labelType() const;

		// CLogItem implementation
		virtual ELogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CLogItemCodeLabel);
	private:
		ECodeLabelType m_eType;
	};
}