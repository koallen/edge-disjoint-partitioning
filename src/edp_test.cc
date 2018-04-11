#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_set>
#include "algorithms.h"

using namespace std;

static const uint32_t INF = numeric_limits<uint32_t>::max();

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: ./edp /path/to/graph num_of_labels" << endl;
		exit(-1);
	}
	cout << "----Stage 1: initialization----" << endl;
	string input(argv[1]);
	uint32_t num_of_labels = atoi(argv[2]);
	auto index = RunAlgorithmOne(input, num_of_labels);
	cout << "Created index" << endl;

	cout << "----Stage 2: query processing----" << endl;
	unordered_set<uint32_t> labels;
	labels.insert(5);
	labels.insert(3);
	uint32_t src = 0, dst = 60500;
	for (size_t i = 0; i < 5; ++i)
	{
		auto t1 = chrono::high_resolution_clock::now();
		uint32_t cost = RunAlgorithmTwo(index, src, dst, labels);
		auto t2 = chrono::high_resolution_clock::now();

		if (cost == INF)
			cout << "Cannot find a route" << endl;
		else
		{
			cout << "Finished, cost is " << cost << " from " << src << " to " << dst << " with labels ";
			for (auto&& l : labels)
				cout << l << " ";
			cout << endl;
		}

		auto diff = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
		cout << "Time taken to run the query: " << diff.count() << "ns" << endl;
	}

	return 0;
}
