#pragma once
#include <list>
#include "Node.h"

namespace ai
{
	class Graph
	{
	public:
		explicit	Graph(unsigned int n);							// Constructs a graph containing n Nodes

		Node&		AddNode(unsigned int index, float x, float y);	// Adds an empty node with the given index. Returns the created node
		Node*		GetNode(unsigned int index);					// Returns a pointer to the node at the given index or nullptr if it doesn't exist

	private:
		std::list<Node>	m_nodes;									// A linked list containing all the graph's nodes
	};
}
