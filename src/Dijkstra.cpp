#include "Dijkstra.h"
#include "globals.h"
#include <set>
using namespace std;

static vector<double> dist;

static bool
cmp(vertex_t u, vertex_t v) {
	return (dist.at(u) < dist.at(v));
}

Dijkstra::Dijkstra(const Graph& g): Graph(g), source(0) {}

double
Dijkstra::dist_from_source(vertex_t u) {
	return dist.at(u);
}

void
Dijkstra::shortest_path(void) {
	int len = get_num_vertices();

	set<int,bool(*)(int,int)> q(cmp);
	//set<int,bool(*)(int,int)> queue(cmp_dist);

	dist = vector<double>(len, INFINITY);
	prev = vector<vertex_t>(len, -1);

	dist.at(source) = 0; /* Distance from source to source */
	for (int i=0; i<len; i++) {
		q.insert(i);
	}

	while (!q.empty()) {
		auto top = q.begin();	/* Visit v in queue with min dist */
		auto v = get_vertex(*top);
		q.erase(top);

		/* For ea vertex u in adj(v) */
		for (auto e : v->get_adj()) {	
			auto edge = get_edge(e);
			vertex_t u = edge->adj(v->get_id());

			double alt = dist.at(v->get_id()) + edge->get_cost();

			/* If dist(v) + e < dist(u), update dist(u) */
			if (alt < dist.at(u)) {	
				q.erase(u);
				dist.at(u) = alt;
				q.insert(u);
				prev.at(u) = v->get_id();
			}
		}

	}

}

