#include "Kruskall.h"
#include "Edge.h"

#include <algorithm> /* std::sort */
#include <memory>

bool compareEdges(shared_ptr<Edge> a, shared_ptr<Edge> b) {
	return a->get_cost() < b->get_cost();
}

Kruskall::Kruskall(string pathname): Graph(pathname) {
	findMST();
}

void
Kruskall::findMST(void) {
	// Make |V| singleton sets of all vertices in V
	sort(edge_list.begin(), edge_list.end(), compareEdges);
	/* For ea edge e=(u,v), if set(u) != set(v), add edge and union set(u) U set(v) */
}