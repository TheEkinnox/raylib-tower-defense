#include "pch.h"

#include "Dijkstra.h"
#include "OpenClosedLists.h"

#include <iostream>

namespace ai
{
	bool DijkstraPathFinder::PathFind(const Graph& graph, const Node& start, const Node& goal)
	{
		OpenNodeList<PathRecord> openList;
		ClosedNodeList<PathRecord> closedList;
		PathRecord current;

		openList += PathRecord{ nullptr, &start, nullptr, 0 };

		while (!openList.IsEmpty())
		{
			current = openList.PopSmallestCostSoFarNode();

			if (current.Node->GetIndex() == goal.GetIndex())
				break;

			const Node::EdgeList& connections = current.Node->GetConnections();

			for (const Edge& connection : connections)
			{
				if (closedList.Find(*connection.To) != nullptr)
					continue;

				const unsigned int endCost = current.CostSoFar + connection.Cost;
				PathRecord* connectionRecord = openList.Find(*connection.To);

				if (connectionRecord != nullptr)
				{
					if (connectionRecord->CostSoFar <= endCost)
						continue;

					*connectionRecord = PathRecord{ current.Node, connection.To, &connection, endCost };

					openList.SortByCostSoFar();
				}
				else
					openList += PathRecord{ current.Node, connection.To, &connection, endCost };
			}

			openList -= current;
			closedList += current;
		}

		m_path.clear();

		if (current.Node->GetIndex() != goal.GetIndex())
			return false;

		while (current.Node != &start)
		{
			m_path.push_back(*current.Connection);
			current = *closedList.Find(*current.Origin);
		}

		std::reverse(m_path.begin(), m_path.end());

		return true;
	}
}
