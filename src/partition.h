#include "edge.h"
#include "vertex.h"
#include <vector>
#include <unordered_set>

struct VertexHasher
{
	size_t operator()(const Vertex& obj) const;
};

struct VertexComparator
{
	bool operator()(const Vertex& obj1, const Vertex& obj2) const;
};

class Partition
{
	private:
		std::unordered_set<Vertex, VertexHasher, VertexComparator> vertices_;
		std::vector<Edge> edges_;
	public:
		bool Contains(uint32_t vertex_id);
		void AddVertex(uint32_t id, bool is_bridge, std::vector<uint32_t>&& other_hosts);
		void AddEdge(uint32_t src, uint32_t dst, uint32_t weight);
};
