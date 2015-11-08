#include "Graph.h"

Graph::Graph(int num_v) {
	for (int i=0; i<num_v; i++) {
		vertex_list.push_back(make_shared<Vertex>(Vertex(i)));
	}
}

shared_ptr<Edge>
Graph::adj_get(vertex_t vid) {
	if (vid >= vertex_list.size())
		return nullptr;
	shared_ptr<Vertex> sp_v = vertex_list.at(vid);
	edge_t eid = sp_v->get();

	if (eid >= edge_list.size()) 
		return nullptr;
	
	return edge_list.at(eid);
}