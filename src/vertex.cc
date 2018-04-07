#include "vertex.h"

using namespace std;

Vertex::Vertex(uint32_t id) : id_(id) {}

Vertex::Vertex(uint32_t id, bool is_bridge, vector<uint32_t>&& other_hosts) :
	id_(id), is_bridge_(is_bridge), other_hosts_(move(other_hosts))
{}

uint32_t Vertex::GetId() const
{
	return id_;
}

bool Vertex::IsBridge() const
{
	return is_bridge_;
}

vector<uint32_t>& Vertex::GetOtherHosts()
{
	return other_hosts_;
}
