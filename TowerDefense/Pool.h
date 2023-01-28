#pragma once
#include "Bullet.h"
#include "PooledObject.h"
#include <vector>

namespace TD
{
	template <typename T>
	class Pool
	{
	private:
		std::vector <T*> m_objects;

	public:
		~Pool();

		template <typename ... Args>
		T&		GetObject(Args&... args);

		void	Update();
		void	Clear();
	};

	template <typename T>
	Pool<T>::~Pool()
	{
		Clear();
	}

	template <typename T>
	void Pool<T>::Update()
	{
		for (T* object : m_objects)
			if (object->IsActive())
				object->Update();
	}

	template <typename T>
	void Pool<T>::Clear()
	{
		for (T* object : m_objects)
			if (object != nullptr)
				delete object;

		m_objects.clear();
	}

	template <typename T>
	template <typename ... Args>
	T& Pool<T>::GetObject(Args&... args)
	{
		if (!std::is_base_of_v<PooledObject, T>)
			throw; // TODO: Throw invalid_argument exception

		for (size_t i = 0; i < m_objects.size(); i++)
		{
			if (!m_objects[i]->IsActive())
			{
				m_objects[i]->~T();
				new (m_objects[i]) T(args...);
				m_objects[i]->SetActive(true);
				return *m_objects[i];
			}
		}

		T* obj = new T(args...);
		obj->SetActive(true);

		m_objects.push_back(obj);

		return *obj;
	}
}