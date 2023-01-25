#include "pch.h"
#include "IPathFinder.h"

namespace ai
{
	Node::EdgeList IPathFinder::GetPath() const
	{
		return m_path;
	}

	const Edge* IPathFinder::GetPathEdge(const unsigned int index) const
	{
		if (m_path.empty() || index == m_path[m_path.size() - 1].To->GetIndex())
			return nullptr;

		for (size_t i = 0; i < m_path.size() - 1; i++)
			if (m_path[i].To->GetIndex() == index)
				return &m_path[i + 1];

		return m_path.data();
	}
}
