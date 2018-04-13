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
		cerr << "Usage: ./edp /path/to/graph num_of_labels num_of_vertices" << endl;
		exit(-1);
	}

	cerr << "----Stage 1: initialization----" << endl;
	string input(argv[1]);
	uint32_t num_of_labels = atoi(argv[2]);
	auto index = RunAlgorithmOne(input, num_of_labels);
	cerr << "Created index" << endl;

	cerr << "----Stage 2: query processing----" << endl;
	uint32_t num_of_vertices = atoi(argv[3]);
	RandomGenerator rng;
	rng.seed(random_device()());
	uniform_int_distribution<uint32_t> label_dist(0, num_of_labels);
	uniform_int_distribution<uint32_t> vertex_dist(0, num_of_vertices);

	uint32_t num_of_queries = 1000;
	for (uint32_t iter = 0; iter < num_of_queries; ++iter)
	{
		// generate query labels
		unordered_set<uint32_t> labels;
		while (labels.size() < num_of_labels / 2)
			labels.insert(label_dist(rng));
#ifndef NDEBUG
		for (uint32_t label:labels)
			cerr << "label: " << label << endl;
#endif

		// run query
		cerr << "query num: " << iter << endl;
		uint32_t src;
		do {
			src = vertex_dist(rng);
		} while (index.GetMinPr(src, labels) == INF);
		uint32_t dst = vertex_dist(rng);
		cerr << "src: " << src << ", dst: " << dst << endl;

		auto t1 = chrono::high_resolution_clock::now();
		uint32_t cost = RunAlgorithmTwo(index, src, dst, labels);
		auto t2 = chrono::high_resolution_clock::now();

		if (cost == INF)
			cerr << "Cannot find a route" << endl;
		else
		{
			cerr << "Finished, cost is " << cost << " from " << src << " to " << dst << " with labels ";
			for (auto&& l : labels)
				cerr << l << " ";
			cerr << endl;
		}

		uint32_t total_entries = 0;
		for (uint32_t l = 0; l < num_of_labels; ++l)
			total_entries += index.GetPartition(l).GetCostSize();
		cerr << "Now there are " << total_entries << " entries in index" << endl;
		cout << total_entries << endl;

		auto diff = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
		cerr << "Time taken to run the query: " << diff.count() << "ms" << endl;
		cerr << "========================================" << endl;
	}

	return 0;
}
