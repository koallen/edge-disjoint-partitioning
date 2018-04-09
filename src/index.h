#ifndef INDEX_H_
#define INDEX_H_
#include <vector>
#include <unordered_map>
#include "partition.h"

class Index
{
	private:
		std::unordered_map<uint32_t, Partition> partitions_;
	public:
		Partition& GetPartition(uint32_t label);
		std::vector<uint32_t>& GetOtherHosts(uint32_t label, uint32_t vertex_id);
		uint32_t GetMinPr(uint32_t src);
		bool IsBridge(uint32_t label, uint32_t vertex_id);
		void CreatePartition(uint32_t label);
};
#endif
