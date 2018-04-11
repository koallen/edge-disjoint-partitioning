#ifndef PARTITION_H_
#define PARTITION_H_
#include "vertex.h"
#include <vector>
#include <unordered_map>

class Partition
{
	private:
		std::unordered_map<uint32_t, Vertex> vertices_;
		std::unordered_map<uint64_t, uint32_t> costs_;
	public:
		bool Contains(uint32_t vertex_id);
		void AddVertex(uint32_t id, bool is_bridge, std::vector<uint32_t>&& other_hosts);
		void AddEdge(uint32_t src, uint32_t dst, uint32_t weight);
		bool IsBridge(uint32_t vertex_id);
		Vertex& GetVertex(uint32_t vertex_id);
		std::vector<Edge>& GetEdges(uint32_t vertex_id);
		bool ContainsCost(uint32_t src, uint32_t dst);
		void AddCost(uint32_t src, uint32_t dst, uint32_t distance);
		uint32_t GetCost(uint32_t src, uint32_t dst);
};
#endif
