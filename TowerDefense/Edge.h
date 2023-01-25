#pragma once

namespace ai
{
	class Node;

	struct Edge
	{
		const Node*		To = nullptr;	// The target node of this edge
		unsigned int	Cost = 0;		// The cost of movement on this edge
	};
}
