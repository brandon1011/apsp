#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <memory>

#include "globals.h"
#include "Edge.h"
using namespace std;

class Vertex {
public:
	Vertex(vertex_t id);
	edge_t 	add_edge(edge_t e);

	/* Adj list accessors */
	edge_t 	next(void);		/* Increment adj list iterator */
	edge_t 	get(void);		/* Retrieve current edge in adj list */

	int 	length(void);	/* Num edges in adjaceny list */
	vertex_t get_id(void);

private:
	vector<edge_t> adj;	// Adjacency list
	vertex_t id;	// Unique id for this vertex
	int it;
};

inline
Vertex::Vertex(vertex_t tid): id(tid), it(0) {}

inline int
Vertex::length(void) {
	return adj.size();
}

#endif //VERTEX_H