#pragma once
// NES log item for code label

#include <cassert>
#include "DClass.h"
#include "CNesLogItem.h"
#include "ENesCodeLabelType.h"

namespace PurrFX
{
	class CNesLogItemCodeLabel: public CNesLogItem
	{
	public:
		CNesLogItemCodeLabel(ENesCodeLabelType i_eType);

		ENesCodeLabelType labelType() const;

		// CNesLogItem implementation
		virtual ENesLogItemType type() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesLogItemCodeLabel);
	private:
		ENesCodeLabelType m_eType;
	};
}