#include "partition.h"

using namespace std;

bool Partition::Contains(uint32_t vertex_id)
{
	return vertices_.find(vertex_id) != vertices_.end();
}

void Partition::AddVertex(uint32_t id, bool is_bridge, vector<uint32_t>&& other_hosts)
{
	vertices_.insert({id, Vertex(id, is_bridge, move(other_hosts))});
}

void Partition::AddEdge(uint32_t src, uint32_t dst, uint32_t weight)
{
	vertices_.find(src)->second.AddEdge(dst, weight);
}

Vertex& Partition::GetVertex(uint32_t vertex_id)
{
	return vertices_.find(vertex_id)->second;
}

bool Partition::IsBridge(uint32_t vertex_id)
{
	return vertices_.find(vertex_id)->second.IsBridge();
}

vector<Edge>& Partition::GetEdges(uint32_t vertex_id)
{
	return vertices_.find(vertex_id)->second.GetEdges();
}

bool Partition::ContainsCost(uint32_t src, uint32_t dst)
{
	uint64_t key = static_cast<uint64_t>(src) << 32;
	key += static_cast<uint64_t>(dst);
	return costs_.find(key) != costs_.end();
}

void Partition::AddCost(uint32_t src, uint32_t dst, uint32_t distance)
{
	uint64_t key = static_cast<uint64_t>(src) << 32;
	key += static_cast<uint64_t>(dst);
	costs_[key] = distance;
}

uint32_t Partition::GetCost(uint32_t src, uint32_t dst)
{
	uint64_t key = static_cast<uint64_t>(src) << 32;
	key += static_cast<uint64_t>(dst);
	return costs_[key];
}

uint32_t Partition::GetCostSize()
{
	return costs_.size();
}
