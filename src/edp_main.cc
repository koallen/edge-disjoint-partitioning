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



    return 0;
}