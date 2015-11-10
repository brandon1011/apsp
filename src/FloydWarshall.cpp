#include "FloydWarshall.h"
#include <limits>

FloydWarshall::FloydWarshall(string pathname): Graph(pathname) {
	double infty = std::numeric_limits<double>::max();
	num_vertices = vertex_list.size();
	distance_table = vector<vector<double> >(num_vertices);

	for(int i=0; i<num_vertices; i++) {
		/* Initialize distance between each i,j to infinity */
		distance_table.at(i) = vector<double>(num_vertices, infty);
	}
	planPaths();
}

void
FloydWarshall::planPaths(void) {
	/* Reflexive: distance(u,u) = 0 */
	for (int i=0; i<num_vertices; i++) {
		distance_table.at(i).at(i) = 0;
	}

	/* For each edge e = (u,v), distance(u,v) = cost(e) */
	for (int i=0; i<edge_list.size(); i++) {
		shared_ptr<Edge> e = edge_list.at(i);
		vertex_t v = e->get_v();
		vertex_t u = e->get_u();

		distance_table.at(v).at(u) = e->get_cost();
		distance_table.at(u).at(v) = e->get_cost();
	}

	for (int k=0; k<num_vertices;k++) {
		for (int i=0; i<num_vertices; i++) {
			for (int j=0; j<num_vertices; j++) {
				int ab = distance_table.at(i).at(j);
				int ac = distance_table.at(i).at(k);
				int cb = distance_table.at(k).at(j);
				
				if (ab > ac + cb) {
					distance_table.at(i).at(j) = ac + cb;
				}
			}
		}
	}

}