#include "pch.h"
#include "Node.h"

namespace ai
{
	Node::Node() : Node(0, 0, 0)
	{
	}

	Node::Node(const unsigned int& index, const float x, const float y) :
		m_index(index), m_position(x, y)
	{
	}

	bool Node::operator==(const Node& other) const
	{
		return m_index == other.m_index;
	}

	void Node::AddEdge(const Node* to, const unsigned int cost)
	{
		m_connections.push_back(Edge{ to, cost });
	}

	const Node::EdgeList& Node::GetConnections() const
	{
		return m_connections;
	}

	unsigned int Node::GetIndex() const
	{
		return m_index;
	}

	Node::Vector2 Node::GetPosition() const
	{
		return m_position;
	}
}
