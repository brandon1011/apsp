#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "Graph.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class FloydWarshall : public Graph {
public:
	FloydWarshall(const Graph& g);
	double lookup(vertex_t v, vertex_t u);

private:
	void 	planPaths(void);
	int		num_vertices;
	vector<vector<double>>	distance_table;	/* element[i][j] is distance btw vertex i & j */
};

inline double
FloydWarshall::lookup(vertex_t v, vertex_t u) {
	return distance_table.at(u).at(v);
}

#endif //FLOYD_WARSHALL_H