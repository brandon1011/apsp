#include "Kruskall.h"
#include "Edge.h"
#include "UnionFind.h"

#include <algorithm> /* std::sort */
#include <memory>

Kruskall::Kruskall(const Graph& other): Graph(other) {
	findMST();
}

void
Kruskall::findMST(void) {
	UnionFind sets(vertex_list.size()); /* Make |V| singleton sets for v in V */
	sort(edge_list.begin(), edge_list.end(), Graph::compare_edges);

	/* For ea edge e=(u,v), if set(u) != set(v), add edge and union set(u) U set(v) */
	for (auto edge: edge_list) {
		vertex_t u = edge->get_u();
		vertex_t v = edge->get_v();

		if (sets.set_find(u) != sets.set_find(v)) {
			sets.set_union(u,v);
			mst.push_back(edge);
		}
	}
	/* Replace edge_list with Minimum spanning tree */
	edge_list = vector<shared_ptr<Edge> >(mst);
}