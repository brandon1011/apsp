#include "Kruskall.h"
#include "Edge.h"
#include "UnionFind.h"

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
	UnionFind sets(vertex_list.size()); /* Make |V| singleton sets for v in V */
	sort(edge_list.begin(), edge_list.end(), compareEdges);

	/* For ea edge e=(u,v), if set(u) != set(v), add edge and union set(u) U set(v) */
	for (auto edge: edge_list) {
		vertex_t u = edge->get_u();
		vertex_t v = edge->get_v();

		if (sets.set_find(u) != sets.set_find(v)) {
			sets.set_union(u,v);
			mst.push_back(edge);
		}
	}
}