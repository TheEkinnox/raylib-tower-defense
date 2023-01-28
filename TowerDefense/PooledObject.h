#pragma once

namespace TD
{
	class PooledObject
	{
	public:
						PooledObject();
		virtual			~PooledObject() = default;
		virtual void	SetActive(bool active);
		bool			IsActive() const;

		virtual void	Update() = 0;

	private:
		bool			m_active;
	};
}