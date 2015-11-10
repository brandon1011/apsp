#include "Graph.h"

#include <fstream>
#include <sstream>
#include <iostream>

Graph::Graph(int num_v) {
	for (int i=0; i<num_v; i++) {
		vertex_list.push_back(make_shared<Vertex>(Vertex(i)));
	}
}

Graph::Graph(string pathname) {
	string line;
	int len;	/* Num vertices in the graph */

	ifstream file(pathname);

	if (file.is_open()) {

		getline(file,line);
		stringstream stream(line);
		stream >> len;

		/* Initialize the vertex list */
		for (int i=0; i<len; i++) {
			vertex_list.push_back(make_shared<Vertex>(Vertex(i)));
		}


		while(getline(file,line) && line.size()) {
			/* Parse each line in file and create edge */
			stringstream stream(line);
			vertex_t v,u;	/* Vertex indices of e=(u,v) */
			double cost;	/* Cost of the edge */

			stream >> u;
			stream >> v;
			stream >> cost;
			add_edge(u,v,cost);
		}

		file.close();
	} 
	else 
		std::cerr << "Error! Could not open file " + pathname << std::endl;

}

shared_ptr<Edge>
Graph::adj_get_edge(vertex_t vid) {
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
	return adj_get_edge(vid);

}

shared_ptr<Vertex> 
Graph::adj_get_vertex(vertex_t v) {
	shared_ptr<Edge> edge = adj_get_edge(v);
	if (edge == nullptr) return nullptr;

	vertex_t vid = edge->adj(v);
	if (vid >= vertex_list.size()) return nullptr;

	return vertex_list.at(vid);
}

shared_ptr<Edge>
Graph::add_edge(vertex_t u, vertex_t v, double cost) {
	edge_t eid = edge_list.size();

	/* Check bounds of u,v */
	if (u >= vertex_list.size() || v >= vertex_list.size()) 
		return nullptr;

	/* Add new edge to u,v adj list */
	vertex_list.at(u)->add_edge(eid);
	vertex_list.at(v)->add_edge(eid);

	shared_ptr<Edge> sp_e = make_shared<Edge>(Edge(eid, u, v, cost));
	edge_list.push_back(sp_e);	/* Append to edge list */

	return sp_e;
}

void
Graph::display(void) {
	std::cout<<"Num vertices = "<<vertex_list.size()<<"\nEdges in the graph:\n";

	for (auto edge : edge_list) {
		vertex_t u = edge->get_u();
		vertex_t v = edge->get_v();
		double cost = edge->get_cost();

		std::cout << "(" << u << "," << v << ")\tc=" << cost << std::	endl;
	}
}