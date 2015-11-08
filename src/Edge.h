#ifndef EDGE_H
#define EDGE_H

#include <memory>
#include "globals.h"
#include "Vertex.h"


class Edge {
public:
	Edge(edge_t id, vertex_t v, vertex_t u, int cost);
	vertex_t 	adj(vertex_t x);
	int 		get_cost(void);
	edge_t		get_id(void);
private:
	int 		cost;	// Edge cost
	edge_t		id;		// Edge identifier
	vertex_t	u;
	vertex_t	v;
};

inline
Edge::Edge(edge_t tid, vertex_t tv, vertex_t tu, int cost): 
	id(tid), v(tv), u(tu), cost(cost) {}

inline
vertex_t Edge::adj(vertex_t x) {
	if (x == u) return v;
	else if (x == v) return u;
	else return INVALID_VERTEX;
}

inline
int Edge::get_cost(void) {
	return cost;
}

inline
int Edge::get_id(void) {
	return id;
}

#endif //EDGE_H