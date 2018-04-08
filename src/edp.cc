#include <iostream>
#include "index.h"
#include "partition.h"
#include "vertex.h"

using namespace std;

Index RunAlgorithmOne()
{
	Index index;
	index.CreatePartition(0);
	auto par = index.GetPartition(0);
	vector<uint32_t> other_hosts_;
	for (size_t i = 0; i < 10; ++i)
		other_hosts_.push_back(i);
	par.AddVertex(0, true, move(other_hosts_));
	par.AddEdge(0, 1, 100);
	cout << "Run algorithm 1" << endl;

	return index;
}

void RunAlgorithmTwo()
{
	cout << "Run algorithm 2" << endl;
}

int main()
{
	auto index = RunAlgorithmOne();
	RunAlgorithmTwo();
	cout << "Finished" << endl;
}
