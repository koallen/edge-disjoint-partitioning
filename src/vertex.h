#include <vector>
#include <cstdint>

class Vertex
{
	private:
		uint32_t id_;
		bool is_bridge_;
		std::vector<uint32_t> other_hosts_;
	public:
		Vertex(uint32_t id);
		Vertex(uint32_t id, bool is_bridge, std::vector<uint32_t>&& other_hosts);
		uint32_t GetId() const;
		bool IsBridge() const;
		std::vector<uint32_t>& GetOtherHosts();
};
