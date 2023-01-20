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
		T& GetObject(Args... args);

		void Update();
	};

	template <typename T>
	TD::Pool<T>::~Pool()
	{
		for (PooledObject* object : m_objects)
			delete object;

		m_objects.clear();
	}

	template <typename T>
	void TD::Pool<T>::Update()
	{
		for (PooledObject* object : m_objects)
			if (object->IsActive())
				object->Update();
	}
	
	template <typename T>
	template <typename ... Args>
	inline T& Pool<T>::GetObject(Args... args)
	{
		if (!std::is_base_of_v<PooledObject, T>)
			throw; // TODO: Throw invalid_argument exception

		for (size_t i = 0; i < m_objects.size(); i++)
		{
			if (!m_objects[i]->IsActive())
			{
				m_objects[i]->SetActive(true);
				new (m_objects[i]) T(args...);
				return *reinterpret_cast<T*>(m_objects[i]);
			}
		}

		T* obj = new T(args...);
		obj->SetActive(true);

		m_objects.push_back(obj);

		return *obj;
	}
}