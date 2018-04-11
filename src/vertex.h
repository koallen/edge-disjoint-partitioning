#ifndef VERTEX_H_
#define VERTEX_H_
#include <vector>
#include <unordered_set>
#include <cstdint>

struct Edge {
	uint32_t dst, weight;
	Edge(uint32_t dst, uint32_t weight);
};

class Vertex
{
	private:
		uint32_t id_;
		bool is_bridge_;
		std::vector<uint32_t> other_hosts_;
		std::vector<uint32_t> bridge_edges_;
		std::vector<Edge> edges_;
	public:
		Vertex(uint32_t id, bool is_bridge, std::vector<uint32_t>&& other_host);
		uint32_t GetId() const;
		bool IsBridge() const;
		std::vector<uint32_t>& GetOtherHosts();
		void AddEdge(uint32_t dst, uint32_t weight);
		std::vector<Edge>& GetEdges();
		std::vector<uint32_t>& GetBridgeEdges();
		void AddBridgeEdge(uint32_t dst);
};
#endif
