#include "partition.h"

using namespace std;

// size_t VertexHasher::operator()(const Vertex& obj) const
// {
// 	return std::hash<uint32_t>()(obj.GetId());
// }

// bool VertexComparator::operator()(const Vertex& obj1, const Vertex& obj2) const
// {
// 	return obj1.GetId() == obj2.GetId();
// }

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
	auto it = vertices_.find(src);
	it->second.AddEdge(dst, weight);
}
