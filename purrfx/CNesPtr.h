#pragma once
// Use this class to create any particular CNes implementation

#include <cassert>
#include "DClass.h"
#include "ENesType.h"
#include "CNes.h"

namespace PurrFX
{
	class CNesPtr final
	{
	public:
		CNesPtr(ENesType i_eType);
		~CNesPtr();

		CNes* operator->() const;

		CLASS_DISABLE_DEFAULT_CONSTRUCTOR(CNesPtr)
		CLASS_MAKE_NON_COPYABLE(CNesPtr)
	private:
		CNes* m_pNes = nullptr;
	};
}