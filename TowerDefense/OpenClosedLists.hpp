#pragma once
#include <stdexcept>
#include <algorithm>

namespace ai
{
	template <class PathRecord>
	OpenNodeList<PathRecord>& OpenNodeList<PathRecord>::operator+=(const PathRecord& node)
	{
		m_recordsQueue.push_back(node);

		SortByCostSoFar();

		return *this;
	}

	template <class PathRecord>
	OpenNodeList<PathRecord>& OpenNodeList<PathRecord>::operator-=(const PathRecord& node)
	{
		for (size_t i = 0; i < m_recordsQueue.size(); i++)
		{
			if (&m_recordsQueue[i] == &node)
			{
				for (size_t j = i + 1; j < m_recordsQueue.size(); j++)
					m_recordsQueue[j - 1] = m_recordsQueue[j];

				m_recordsQueue.resize(m_recordsQueue.size() - 1);

				break;
			}
		}

		return *this;
	}

	template <class PathRecord>
	bool OpenNodeList<PathRecord>::IsEmpty() const
	{
		return m_recordsQueue.empty();
	}

	template <class PathRecord>
	PathRecord OpenNodeList<PathRecord>::PopSmallestCostSoFarNode()
	{
		if (IsEmpty())
			throw std::out_of_range("Unable to pop smallest cost so far node - empty list");

		PathRecord& min = m_recordsQueue[0];

		for (const PathRecord& pathRecord : m_recordsQueue)
			if (pathRecord.CostSoFar < min.CostSoFar)
				min = pathRecord;

		*this -= min;
		return min;
	}

	template <class PathRecord>
	PathRecord* OpenNodeList<PathRecord>::Find(const Node& node)
	{
		for (PathRecord& pathRecord : m_recordsQueue)
			if (pathRecord.Node == &node)
				return &pathRecord;

		return nullptr;
	}

	template <class PathRecord>
	void OpenNodeList<PathRecord>::SortByCostSoFar()
	{
		auto compareRecords = [](const PathRecord l, const PathRecord r)
		{
			return l.CostSoFar < r.CostSoFar;
		};

		std::sort(m_recordsQueue.begin(), m_recordsQueue.end(), compareRecords);
	}

	template <class PathRecord>
	ClosedNodeList<PathRecord>& ClosedNodeList<PathRecord>::operator+=(const PathRecord& node)
	{
		m_recordsQueue.push_back(node);

		return *this;
	}

	template <class PathRecord>
	bool ClosedNodeList<PathRecord>::Contains(Node* node) const
	{
		auto isNodeRecord = [node](const PathRecord p)
		{
			return p.Node == node;
		};

		return std::any_of(m_recordsQueue.begin(), m_recordsQueue.end(), isNodeRecord);
	}

	template <class PathRecord>
	PathRecord* ClosedNodeList<PathRecord>::Find(const Node& node)
	{
		for (PathRecord& pathRecord : m_recordsQueue)
			if (pathRecord.Node == &node)
				return &pathRecord;

		return nullptr;
	}
}
