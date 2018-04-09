#include "index.h"
#include <utility>

using namespace std;

void Index::CreatePartition(uint32_t label)
{
    partitions_.insert(make_pair(label, Partition()));
}

uint32_t Index::GetMinPr(uint32_t src)
{
	uint32_t min = 100000000;
	uint32_t label;
	for (auto&& p : partitions_)
	{
		auto& par = p.second;
		if (par.Contains(src))
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
