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
	shared_ptr<Edge> adj_get(vertex_t v);
	
private:
	vector<shared_ptr<Vertex>> 	vertex_list;
	vector<shared_ptr<Edge>>	edge_list;
};

#endif //GRAPH_H