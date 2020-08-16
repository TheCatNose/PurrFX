#include "CNesLogItemCodeLabel.h"

namespace PurrFX
{
	CNesLogItemCodeLabel::CNesLogItemCodeLabel(ENesCodeLabelType i_eType):
		m_eType(i_eType)
	{
		assert(m_eType != ENesCodeLabelType::Undefined);
	}

	ENesCodeLabelType CNesLogItemCodeLabel::labelType() const
	{
		return m_eType;
	}

	ENesLogItemType CNesLogItemCodeLabel::type() const
	{
		return ENesLogItemType::CodeLabel;
	}
}