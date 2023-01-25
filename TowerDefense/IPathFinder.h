#pragma once
#include "node.h"

namespace ai
{
	class Graph;

	class IPathFinder
	{
	public:
		virtual			~IPathFinder() = default;

		virtual bool	PathFind(const Graph& graph, const Node& start, const Node& goal) = 0;
		Node::EdgeList	GetPath() const;
		const Edge*		GetPathEdge(unsigned int index) const;

	protected:
		Node::EdgeList	m_path;
	};
}
