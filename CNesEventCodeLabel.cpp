#include "CNesEventCodeLabel.h"

namespace PurrFX
{
	CNesEventCodeLabel::CNesEventCodeLabel(ECodeLabelType i_eType):
		m_eType(i_eType)
	{
		assert(m_eType != ECodeLabelType::Undefined);
	}

	ECodeLabelType CNesEventCodeLabel::labelType() const
	{
		return m_eType;
	}

	ENesEventType CNesEventCodeLabel::type() const
	{
		return ENesEventType::CodeLabel;
	}
}