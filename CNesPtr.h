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
		CLASS_MAKE_NON_COPYABLE(CNesPtr)
	public:
		CNesPtr();
		CNesPtr(ENesType i_eType);
		~CNesPtr();

		CNes* operator->() const;

	private:
		CNes* m_pNes = nullptr;
	};
}