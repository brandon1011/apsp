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
	Graph(const Graph& other);	/* Copy constructor */
	Graph(string pathname);

	/* Vertex adj list accessors */
	shared_ptr<Edge> 	adj_get_edge(vertex_t v);
	shared_ptr<Vertex> 	adj_get_vertex(vertex_t v);
	shared_ptr<Edge> 	adj_next(vertex_t v);

	/* Add edge to the graph */
	shared_ptr<Edge> 	add_edge(vertex_t u, vertex_t v, double cost);

	shared_ptr<Vertex> 	get_vertex(vertex_t v);
	shared_ptr<Edge>	get_edge(edge_t e);

	int		get_num_vertices(void);
	int		get_num_edges(void);
	void	display(void);
	
protected:
	vector<shared_ptr<Vertex>> 	vertex_list;
	vector<shared_ptr<Edge>>	edge_list;
};

inline shared_ptr<Vertex>
Graph::get_vertex(vertex_t v) {
	return (v >= vertex_list.size() || v < 0) ? nullptr : vertex_list.at(v);
}

inline shared_ptr<Edge>
Graph::get_edge(edge_t e) {
	return (e >= edge_list.size() || e < 0) ? nullptr : edge_list.at(e);
}

inline int
Graph::get_num_vertices(void) {
	return vertex_list.size();
}

inline int
Graph::get_num_edges(void) {
	return edge_list.size();
}

#endif //GRAPH_H