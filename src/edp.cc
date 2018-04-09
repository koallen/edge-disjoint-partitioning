#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <queue>
#include <limits>
#include <utility>
#include "index.h"
#include "partition.h"
#include "vertex.h"

using namespace std;

const uint32_t INF = numeric_limits<uint32_t>::max();

struct PQElement
{
	uint32_t label, dst, cost;
	PQElement(uint32_t label, uint32_t dst, uint32_t cost) : label(label), dst(dst), cost(cost) {}
};

struct PQCompare
{
	bool operator()(const PQElement& obj1, const PQElement& obj2)
	{
		return obj1.cost > obj2.cost;
	}
};

Index RunAlgorithmOne(string& input_filename, uint32_t num_of_labels)
{
	Index index;
	for (uint32_t i = 0; i < num_of_labels; ++i)
		index.CreatePartition(i);

	ifstream input(input_filename);
	if (!input.is_open())
	{
		cout << "Input file cannot be opened!" << endl;
		exit(-1);
	}

	uint32_t src, dst, weight, label;
	unordered_map<uint32_t, unordered_set<uint32_t> > other_hosts_map;
	while (input >> src >> dst >> weight >> label)
	{
		other_hosts_map[src].insert(label);
	}
	cout << "Finish scanning" << endl;

	ifstream input2(input_filename);
	while (input2 >> src >> dst >> weight >> label)
	{
		auto& par = index.GetPartition(label);
		if (!par.Contains(src))
		{
			bool is_bridge = false;
			vector<uint32_t> other_hosts;
			if (other_hosts_map[src].size() > 1)
			{
				is_bridge = true;
				for (auto&& label_in_map : other_hosts_map[src])
					if (label != label_in_map)
						other_hosts.push_back(label_in_map);
			}
			par.AddVertex(src, is_bridge, move(other_hosts));
			cout << "Added vertex " << src << " " << is_bridge << endl;
		}
		if (!par.Contains(dst))
		{
			bool is_bridge = false;
			vector<uint32_t> other_hosts;
			if (other_hosts_map[dst].size() > 1)
			{
				is_bridge = true;
				for (auto&& label_in_map : other_hosts_map[dst])
					if (label != label_in_map)
						other_hosts.push_back(label_in_map);
			}
			par.AddVertex(dst, is_bridge, move(other_hosts));
			cout << "Added vertex " << dst << " " << is_bridge << endl;
		}
		par.AddEdge(src, dst, weight);
		cout << "Added edge " << src << "->" << dst << endl;
	}

	return index;
}

uint32_t RunAlgorithmTwo(Index& index, uint32_t src, uint32_t dst, unordered_set<uint32_t>& labels)
{
	priority_queue<PQElement, vector<PQElement>, PQCompare> q;
	q.emplace(index.GetMinPr(src), src, 0);

	while (!q.empty())
	{
		auto current_vertex = q.top();
		q.pop();

		cout << "Now visiting " << current_vertex.dst << endl;
		if (current_vertex.dst == dst) return current_vertex.cost;

		if (index.IsBridge(current_vertex.label, current_vertex.dst))
			for (auto&& other_label : index.GetOtherHosts(current_vertex.label, current_vertex.dst))
				if (labels.count(other_label) == 1)
					q.emplace(other_label, current_vertex.dst, current_vertex.cost);

		/*
		 * run Dijkstra and insert into index (i.e. cost hash table)
		 *
		 * dj_q is the pq used for the Dijkstra run
		 */
		{
			auto& par = index.GetPartition(current_vertex.label);
			unordered_map<uint32_t, uint32_t> distances; // currently using a map because ID is not contiguous
			distances[current_vertex.dst] = 0;
			priority_queue<pair<uint32_t, uint32_t>, vector<pair<uint32_t, uint32_t> >, greater<pair<uint32_t, uint32_t> > > dj_q;
			dj_q.emplace(0, current_vertex.dst);
			while (!dj_q.empty())
			{
				auto v = dj_q.top();
				dj_q.pop();
				cout << "Internal: now visiting " << v.second << endl;
				auto it = distances.find(v.second);
				if (it != distances.end() && v.first <= it->second) // ignore redundant entries in PQ
				{
					// insert into outer PQ if v is destination or bridge vertex
					if (v.second == dst)
						q.emplace(0, v.second, current_vertex.cost + it->second);
					else if (par.IsBridge(v.second))
					{
						for (auto&& other_label : index.GetOtherHosts(current_vertex.label, v.second))
							if (labels.count(other_label) == 1)
								q.emplace(other_label, v.second, current_vertex.cost + it->second);
					}
					// loop over the outgoing edges
					for (auto&& edge : par.GetEdges(v.second))
					{
						uint32_t new_weight = v.first + edge.weight;
						auto it = distances.find(edge.dst);
						if (it == distances.end() || it->second > new_weight)
						{
							distances[edge.dst] = new_weight;
							dj_q.emplace(new_weight, edge.dst);
						}
					}
				}
			}
		}
	}

	return INF;
}

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
	labels.insert(0);
	uint32_t src = 0, dst = 1;
	uint32_t cost = RunAlgorithmTwo(index, src, dst, labels);
	if (cost == INF)
		cout << "Cannot find a route" << endl;
	else
		cout << "Finished, cost is " << cost << endl;

	return 0;
}
