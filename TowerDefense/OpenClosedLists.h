#pragma once
#include <vector>

namespace ai
{
	class	Node;
	struct	Edge;

	template <class PathRecord>
	class OpenNodeList
	{
	public:
		OpenNodeList&			operator+=(const PathRecord& node);
		OpenNodeList&			operator-=(const PathRecord& node);
		bool					IsEmpty() const;
		PathRecord				PopSmallestCostSoFarNode();
		PathRecord*				Find(const Node& node);
		void					SortByCostSoFar();

	private:
		std::vector<PathRecord>	m_recordsQueue;
	};

	template <class PathRecord>
	class ClosedNodeList
	{
	public:
		ClosedNodeList&			operator+=(const PathRecord& node);
		bool					Contains(Node* node) const;
		PathRecord*				Find(const Node& node);

	private:
		std::vector<PathRecord>	m_recordsQueue;
	};
}

#include "OpenClosedLists.hpp"
