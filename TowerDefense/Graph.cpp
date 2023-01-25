#include "pch.h"
#include "Graph.h"
#include "Node.h"

namespace ai
{
	Graph::Graph(const unsigned int n)
	{
		for (unsigned int i = 0; i < n; i++)
			AddNode(i, 0, 0);
	}

	Node& Graph::AddNode(unsigned int index, float x, float y)
	{
		m_nodes.emplace_back(index, x, y);

		return m_nodes.back();
	}

	Node* Graph::GetNode(const unsigned int index)
	{
		for (Node& node : m_nodes)
			if (node.GetIndex() == index)
				return &node;

		return nullptr;
	}
}
