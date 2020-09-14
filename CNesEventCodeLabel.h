#pragma once
// NES event: code label

#include <cassert>
#include "DClass.h"
#include "CNesEvent.h"
#include "ECodeLabelType.h"

namespace PurrFX
{
	class CNesEventCodeLabel: public CNesEvent
	{
		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesEventCodeLabel)
	public:
		CNesEventCodeLabel(ECodeLabelType i_eType);

		ECodeLabelType labelType() const;

		// CNesEvent implementation
		virtual ENesEventType type() const;

	private:
		ECodeLabelType m_eType;
	};
}