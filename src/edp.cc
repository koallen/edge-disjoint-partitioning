#include <iostream>
#include "index.h"
#include "partition.h"
#include "vertex.h"

using namespace std;

Index RunAlgorithmOne()
{
	Index index;
	index.CreatePartition(0);
	auto& par = index.GetPartition(0);
	vector<uint32_t> other_hosts_;
	for (size_t i = 0; i < 10; ++i)
		other_hosts_.push_back(i);
	par.AddVertex(0, true, move(other_hosts_));
	par.AddEdge(0, 1, 100);

	// test
	auto& par1 = index.GetPartition(0);
	cout << par1.Contains(0) << endl;
	for (auto&& i : par1.GetEdges(0))
		cout << i.weight << endl;
	cout << "Created index" << endl;

	return index;
}

void RunAlgorithmTwo(Index& index)
{
	auto& par = index.GetPartition(0);
	cout << par.Contains(0) << endl;
}

int main()
{
	cout << "----Stage 1: initialization----" << endl;
	auto index = RunAlgorithmOne();

	cout << "----Stage 2: query processing----" << endl;
	RunAlgorithmTwo(index);
	cout << "Finished" << endl;
}
