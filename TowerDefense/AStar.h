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
		unsigned int	EstimatedTotalCost = 0;
	};

	class IHeuristic
	{
	public:
								IHeuristic() = default;
		virtual					~IHeuristic() = default;
		virtual unsigned int	Evaluate(const Edge& edge) = 0;
	};

	class ManhattanHeuristic : public IHeuristic
	{
	public:
		ManhattanHeuristic(float x, float y);

		unsigned		Evaluate(const Edge& edge) override;

	private:
		Node::Vector2	m_targetPosition;
	};

	class AStarPathFinder : public IPathFinder
	{
	public:
		explicit	AStarPathFinder(IHeuristic& heuristic);

		bool		PathFind(const Graph& graph, const Node& start, const Node& goal) override;

	private:
		IHeuristic*	m_heuristic;
	};
}
