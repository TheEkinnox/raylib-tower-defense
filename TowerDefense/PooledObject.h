#pragma once

namespace TD
{
	class PooledObject
	{
	private:
		bool m_active;

	public:
		void	SetActive(bool active);
		bool	IsActive() const;

		virtual void Update() = 0;
	};
}