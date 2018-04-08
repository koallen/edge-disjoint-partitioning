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

	// test
	//auto& par1 = index.GetPartition(0);
	//cout << par1.Contains(0) << endl;
	//for (auto&& i : par1.GetEdges(0))
	//	cout << i.weight << endl;

	return index;
}

uint32_t RunAlgorithmTwo(Index& index, uint32_t src, uint32_t dst, vector<uint32_t>& labels)
{
	priority_queue<PQElement, vector<PQElement>, PQCompare> q;
	
	// TODO: set correct label here (with min edge cost)
	q.emplace(0, src, 0);

	while (!q.empty())
	{
		auto pq_element = q.top();
		q.pop();

		cout << "Now visiting " << pq_element.dst << endl;
		if (pq_element.dst == dst) return pq_element.cost;

		// run Dijkstra and insert into index (i.e. cost hash table)
		auto& par = index.GetPartition(pq_element.label);
		unordered_map<uint32_t, uint32_t> distances;
		distances[pq_element.dst] = 0;
		priority_queue<pair<uint32_t, uint32_t>, vector<pair<uint32_t, uint32_t> >, greater<pair<uint32_t, uint32_t> > > dj_q;
		dj_q.emplace(0, pq_element.dst);
		while (!dj_q.empty())
		{
			auto dj_element = dj_q.top();
			dj_q.pop();
			cout << "Internal: now visiting " << dj_element.second << endl;
			auto it = distances.find(dj_element.second);
			if (it != distances.end() && dj_element.first <= it->second)
			{
				if (dj_element.second == 1)
					q.emplace(0, dj_element.second, pq_element.cost + it->second);
				for (auto&& edge : par.GetEdges(dj_element.second))
				{
					uint32_t new_weight = dj_element.first + edge.weight;
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
