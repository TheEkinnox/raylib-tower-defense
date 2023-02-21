#include "pch.h"
#include "OpenClosedLists.h"
#include "AStar.h"


namespace ai
{
	ManhattanHeuristic::ManhattanHeuristic(const float x, const float y) :
		m_targetPosition(x, y)
	{
	}

	unsigned int ManhattanHeuristic::Evaluate(const Edge& edge)
	{
		const Node::Vector2 pos = edge.To->GetPosition();

		return static_cast<uint32_t>(abs(pos.m_x - m_targetPosition.m_x) +
			abs(pos.m_y - m_targetPosition.m_y));
	}

	AStarPathFinder::AStarPathFinder(IHeuristic& heuristic) : m_heuristic(&heuristic)
	{
	}

	bool AStarPathFinder::PathFind(const Graph& graph, const Node& start, const Node& goal)
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
				const unsigned int totalCost = endCost + m_heuristic->Evaluate(connection);
				PathRecord* connectionRecord = openList.Find(*connection.To);

				if (connectionRecord != nullptr)
				{
					if (connectionRecord->EstimatedTotalCost <= totalCost)
						continue;

					*connectionRecord = PathRecord{ current.Node, connection.To, &connection, endCost, totalCost };

					openList.SortByCostSoFar();
				}
				else
					openList += PathRecord{ current.Node, connection.To, &connection,
					endCost, totalCost };
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
