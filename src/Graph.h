#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"

#include <vector>
#include <memory>
using namespace std;

class Graph {
public:
	Graph(int num_vertices);

	/* Vertex adj list accessors */
	shared_ptr<Edge> 	adj_get_edge(vertex_t v);
	shared_ptr<Vertex> 	adj_get_vertex(vertex_t v);
	shared_ptr<Edge> 	adj_next(vertex_t v);

	/* Add edge to the graph */
	shared_ptr<Edge> 	add_edge(vertex_t u, vertex_t v, int cost);

	shared_ptr<Vertex> 	get_vertex(vertex_t v);

	
private:
	vector<shared_ptr<Vertex>> 	vertex_list;
	vector<shared_ptr<Edge>>	edge_list;
};

inline shared_ptr<Vertex>
Graph::get_vertex(vertex_t v) {
	return (v >= vertex_list.size() || v < 0) ? nullptr : vertex_list.at(v);
}

#endif //GRAPH_H