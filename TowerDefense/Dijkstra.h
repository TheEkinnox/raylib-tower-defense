#pragma once
#include "IPathFinder.h"

namespace ai
{
	struct PathRecord
	{
		const Node*		Origin = nullptr;
		const Node*		Node = nullptr;
		const Edge*		Connection = nullptr;
		unsigned int	CostSoFar = 0;
	};

	class DijkstraPathFinder : public IPathFinder
	{
	public:
		bool PathFind(const Graph& graph, const Node& start, const Node& goal) override;
	};
}
