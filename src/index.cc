#include "index.h"
#include <utility>
#include <limits>

using namespace std;

const uint32_t INF = numeric_limits<uint32_t>::max();

void Index::CreatePartition(uint32_t label)
{
    partitions_.insert(make_pair(label, Partition()));
}

uint32_t Index::GetMinPr(uint32_t src, unordered_set<uint32_t>& labels)
{
	uint32_t min = INF;
	uint32_t label = INF;
	for (auto&& p : partitions_)
	{
		auto& par = p.second;
		if (par.Contains(src) && labels.count(p.first) == 1)
			for (auto&& edge : par.GetEdges(src))
				if (edge.weight < min)
				{
					min = edge.weight;
					label = p.first;
				}
	}

	return label;
}

bool Index::IsBridge(uint32_t label, uint32_t vertex_id)
{
	return GetPartition(label).IsBridge(vertex_id);
}

vector<uint32_t>& Index::GetOtherHosts(uint32_t label, uint32_t vertex_id)
{
	return GetPartition(label).GetVertex(vertex_id).GetOtherHosts();
}

Partition& Index::GetPartition(uint32_t label)
{
    return partitions_[label];
}

uint32_t Index::GetCost(uint32_t label, uint32_t src, uint32_t dst)
{
	return partitions_[label].GetCost(src, dst);
}

bool Index::ContainsCost(uint32_t label, uint32_t src, uint32_t dst)
{
	return partitions_[label].ContainsCost(src, dst);
}

vector<uint32_t>& Index::GetBridgeEdges(uint32_t label, uint32_t vertex_id)
{
	return partitions_[label].GetVertex(vertex_id).GetBridgeEdges();
}
