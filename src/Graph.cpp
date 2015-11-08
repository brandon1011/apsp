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

shared_ptr<Edge>
Graph::adj_next(vertex_t vid) {
	if (vid >= vertex_list.size())
		return nullptr;
	shared_ptr<Vertex> sp_v = vertex_list.at(vid);
	sp_v->next();
	return adj_get(vid);

}

shared_ptr<Vertex> 
Graph::adj_vertex(vertex_t v) {
	shared_ptr<Edge> edge = adj_get(v);
	if (edge == nullptr) return nullptr;

	vertex_t vid = edge->adj(v);
	if (vid >= vertex_list.size()) return nullptr;

	return vertex_list.at(vid);
}

shared_ptr<Edge>
Graph::add_edge(vertex_t u, vertex_t v, int cost) {
	edge_t eid = edge_list.size();
	/* Check bounds of u, v in v list*/
	shared_ptr<Edge> sp_e = make_shared<Edge>(Edge(eid, u, v, cost));
	/* Add sp_e to edge_list and add eid to u, v adj list*/
	return sp_e;
}
