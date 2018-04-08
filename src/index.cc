#include "index.h"
#include <utility>

using namespace std;

void Index::CreatePartition(uint32_t label)
{
    partitions_.insert(make_pair(label, Partition()));
}

Partition& Index::GetPartition(uint32_t label)
{
    return partitions_.find(label)->second;
}