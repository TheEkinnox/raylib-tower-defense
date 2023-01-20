#include "pch.h"
#include "PooledObject.h"

namespace TD
{
	void PooledObject::SetActive(bool active)
	{ 
		m_active = active;
	};

	bool PooledObject::IsActive() const
	{ 
		return m_active;
	};
}