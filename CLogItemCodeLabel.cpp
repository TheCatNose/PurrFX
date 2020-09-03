#include "CLogItemCodeLabel.h"

namespace PurrFX
{
	CLogItemCodeLabel::CLogItemCodeLabel(ECodeLabelType i_eType):
		m_eType(i_eType)
	{
		assert(m_eType != ECodeLabelType::Undefined);
	}

	ECodeLabelType CLogItemCodeLabel::labelType() const
	{
		return m_eType;
	}

	ELogItemType CLogItemCodeLabel::type() const
	{
		return ELogItemType::CodeLabel;
	}
}