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
			for (auto&& label_in_map : other_hosts_map[src])
			{
				if (label != label_in_map)
					other_hosts.push_back(label_in_map);
			}
			if (!other_hosts.empty())
				is_bridge = true;
			par.AddVertex(src, is_bridge, move(other_hosts));
#ifndef NDEBUG
			cout << "Added vertex " << src << " " << is_bridge << " to partition " << label << " with other hosts ";
			for (auto&& l : par.GetVertex(src).GetOtherHosts())
				cout << l << " ";
			cout << endl;
#endif
		}
		if (!par.Contains(dst))
		{
			bool is_bridge = false;
			vector<uint32_t> other_hosts;
			for (auto&& label_in_map : other_hosts_map[dst])
			{
				if (label != label_in_map)
					other_hosts.push_back(label_in_map);
			}
			if (!other_hosts.empty())
				is_bridge = true;
			par.AddVertex(dst, is_bridge, move(other_hosts));
#ifndef NDEBUG
			cout << "Added vertex " << dst << " " << is_bridge << " to partition " << label << " with other hosts ";
			for (auto&& l : par.GetVertex(dst).GetOtherHosts())
				cout << l << " ";
			cout << endl;
#endif
		}
		par.AddEdge(src, dst, weight);
#ifndef NDEBUG
		cout << "Added edge " << src << "->" << dst << " to partition " << label << endl;
#endif
	}

	return index;
}

void InsertIfRelaxed(priority_queue<PQElement, vector<PQElement>, PQCompare>& q,
	uint32_t label, uint32_t dst, uint32_t distance,
	unordered_map<uint64_t, uint32_t>& global_distance)
{
	uint64_t key = static_cast<uint64_t>(label) << 32;
	key += static_cast<uint64_t>(dst);
	auto it = global_distance.find(key);
	if (it == global_distance.end())
	{
		q.emplace(label, dst, distance);
		global_distance.insert(make_pair(key, distance));
#ifndef NDEBUG
		cout << "Inserted " << dst << " in partition " << label << " into PQ" << endl;
#endif
	}
	else if (it != global_distance.end() && it->second > distance)
	{
		q.emplace(label, dst, distance);
#ifndef NDEBUG
		cout << "Inserted " << dst << " in partition " << label << " into PQ" << endl;
#endif
	}
}

uint32_t RunAlgorithmTwo(Index& index, uint32_t src, uint32_t dst, unordered_set<uint32_t>& labels)
{
	priority_queue<PQElement, vector<PQElement>, PQCompare> q;
	unordered_map<uint64_t, uint32_t> global_distance;

	uint32_t min_par = index.GetMinPr(src, labels);
	if (min_par == INF)
		return INF;
	InsertIfRelaxed(q, min_par, src, 0, global_distance);

	while (!q.empty())
	{
		auto current_vertex = q.top();
		q.pop();

#ifndef NDEBUG
		cout << "Now visiting " << current_vertex.dst << endl;
#endif
		if (current_vertex.dst == dst) return current_vertex.cost;

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
#ifndef NDEBUG
				cout << "Internal: now visiting " << v.second << endl;
#endif
				auto it = distances.find(v.second);
				if (it != distances.end() && v.first == it->second) // ignore redundant entries in PQ
				{
					// insert into outer PQ if v is destination or bridge vertex
					if (v.second == dst)
						InsertIfRelaxed(q, current_vertex.label, v.second,
								current_vertex.cost + it->second, global_distance);
					else if (par.IsBridge(v.second))
					{
						for (auto&& other_label : index.GetOtherHosts(current_vertex.label, v.second))
							if (labels.count(other_label) == 1)
								InsertIfRelaxed(q, other_label, v.second,
										current_vertex.cost + it->second, global_distance);
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
	labels.insert(1);
	uint32_t src = 1, dst = 6;
	uint32_t cost = RunAlgorithmTwo(index, src, dst, labels);
	if (cost == INF)
		cout << "Cannot find a route" << endl;
	else
		cout << "Finished, cost is " << cost << endl;

	return 0;
}
