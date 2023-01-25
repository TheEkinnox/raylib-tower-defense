#pragma once
#include <vector>
#include <Vector.h>
#include "Edge.h"

namespace ai
{
	class Node
	{
	public:
		typedef std::vector<Edge> EdgeList;
		typedef LibMath::Vector2 Vector2;

						Node();
		explicit		Node(const unsigned int& index, float x, float y);	// Constructs a node with the given index

		bool			operator==(const Node& other) const;				// Returns true if the indexes of both nodes are equal

		void			AddEdge(const Node* to, unsigned int cost);			// Add an edge to the given node
		const EdgeList&	GetConnections() const;								// Returns a constant reference to the node's list of edges
		unsigned int	GetIndex() const;									// Returns the index of the node
		Vector2			GetPosition() const;								// Returns the index of the node

	private:
		unsigned int	m_index;											// The index of the node
		Vector2			m_position;											// The position of the node
		EdgeList		m_connections;										// The connections from this node to other nodes
	};
}
