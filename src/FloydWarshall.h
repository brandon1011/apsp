#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "Graph.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class FloydWarshall : public Graph {
public:
	FloydWarshall(string pathname);

private:
	void 	planPaths(void);
	int		num_vertices;
	vector<vector<int>>	distance_table;	/* element[i][j] is distance btw vertex i & j */
};

#endif //FLOYD_WARSHALL_H