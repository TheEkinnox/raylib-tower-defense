#include "pch.h"
#include "PooledObject.h"

namespace TD
{
	PooledObject::PooledObject() : m_active(true)
	{
	}

	void PooledObject::SetActive(const bool active)
	{ 
		m_active = active;
	};

	bool PooledObject::IsActive() const
	{ 
		return m_active;
	};
}