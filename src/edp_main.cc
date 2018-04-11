#include <iostream>
#include <chrono>
#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_set>
#include "algorithms.h"

using namespace std;

static const uint32_t INF = numeric_limits<uint32_t>::max();
typedef mt19937 RandomGenerator;

int main(int argc, char** argv)
{
    if (argc != 4)
	{
		cout << "Usage: ./edp /path/to/graph num_of_labels num_of_vertices" << endl;
		exit(-1);
	}

	cout << "----Stage 1: initialization----" << endl;
	string input(argv[1]);
	uint32_t num_of_labels = atoi(argv[2]);
	auto index = RunAlgorithmOne(input, num_of_labels);
	cout << "Created index" << endl;

	cout << "----Stage 2: query processing----" << endl;
	uint32_t num_of_vertices = atoi(argv[3]);
	unordered_set<uint32_t> labels;
	RandomGenerator rng;
	rng.seed(random_device()());
	uniform_int_distribution<uint32_t> label_dist(0, num_of_labels);
	uniform_int_distribution<uint32_t> vertex_dist(0, num_of_vertices);

	while (labels.size() < num_of_labels/2)
		labels.insert(label_dist(rng));

#ifndef NDEBUG
	for (uint32_t label:labels)
		cout << "label: " << label << endl;
#endif

	uint32_t num_of_qeuries = 2;
	for (uint32_t iter=0; iter < num_of_qeuries; ++iter)
	{
		uint32_t src = vertex_dist(rng);
		uint32_t dst = vertex_dist(rng);

		cout << "src " << src << endl;
		cout << "dst " << dst << endl;

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