#include <iostream>
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

Index RunAlgorithmOne()
{
	Index index;
	index.CreatePartition(0);
	auto& par = index.GetPartition(0);

	vector<uint32_t> other_hosts_0_;
	par.AddVertex(0, false, move(other_hosts_0_));

	vector<uint32_t> other_hosts_1_;
	par.AddVertex(1, false, move(other_hosts_1_));

	par.AddEdge(0, 1, 100);

	return index;
}

uint32_t RunAlgorithmTwo(Index& index, uint32_t src, uint32_t dst, vector<uint32_t>& labels)
{
	priority_queue<PQElement, vector<PQElement>, PQCompare> q;
	
	// TODO: set correct label here (with min edge cost)
	q.emplace(0, src, 0);

	while (!q.empty())
	{
		auto current_vertex = q.top();
		q.pop();

		cout << "Now visiting " << current_vertex.dst << endl;
		if (current_vertex.dst == dst) return current_vertex.cost;

		// TODO: insert intersec with current_vertex

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
					// TODO: make sure the condition is correct
					if (v.second == dst || par.IsBridge(v.second))
						// TODO: intersec with otherhosts list
						q.emplace(0, v.second, current_vertex.cost + it->second);
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

int main()
{
	cout << "----Stage 1: initialization----" << endl;
	auto index = RunAlgorithmOne();
	cout << "Created index" << endl;

	cout << "----Stage 2: query processing----" << endl;
	vector<uint32_t> labels;
	labels.push_back(0);
	uint32_t src = 0, dst = 1;
	uint32_t cost = RunAlgorithmTwo(index, src, dst, labels);
	if (cost == INF)
		cout << "Cannot find a route" << endl;
	else
		cout << "Finished, cost is " << cost << endl;
}
