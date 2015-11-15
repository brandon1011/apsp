#include "Dijkstra.h"
#include "globals.h"
#include <set>
using namespace std;

bool
Dijkstra::cmp(Element u, Element v) {
	return (u.val < v.val);
}

Dijkstra::Dijkstra(const Graph& g): Graph(g), source(0) {}

void
Dijkstra::shortest_path(void) {
	int len = get_num_vertices();

	set<Element,bool(*)(Element,Element)> q(Dijkstra::cmp);

	dist = vector<double>(len, INFINITY);
	prev = vector<vertex_t>(len, -1);

	dist.at(source) = 0; /* Distance from source to source */
	for (int i=0; i<len; i++) {
		q.insert(Element(i,dist.at(i)));
	}

	while (!q.empty()) {
		auto top = q.begin();	/* Visit v in queue with min dist */
		auto v = get_vertex(top->key);
		q.erase(top);

		/* For ea vertex u in adj(v) */
		for (auto e : v->get_adj()) {	
			auto edge = get_edge(e);
			vertex_t u = edge->adj(v->get_id());

			double alt = dist.at(v->get_id()) + edge->get_cost();

			/* If dist(v) + e < dist(u), update dist(u) */
			if (alt < dist.at(u)) {	
				q.erase(Element(u,dist.at(u)));
				dist.at(u) = alt;
				q.insert(Element(u,alt));
				prev.at(u) = v->get_id();
			}
		}

	}

}

