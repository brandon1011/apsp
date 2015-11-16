#ifndef DIJKSTRA_TEST_H
#define DIJKSTRA_TEST_H

#include "../src/Dijkstra.h"
#include "../src/FloydWarshall.h"
#include "../src/Graph.h"

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

#define THRESHOLD 1E-15

inline void
dijkstra_test1(void) {
	Graph g(4);
	g.add_edge(0,1,3.0);
	g.add_edge(0,2,14.0);
	g.add_edge(1,2,2.0);
	g.add_edge(2,3,7.0);
	g.add_edge(0,3, 50.0);

	Dijkstra d(g);
	d.set_source(0);
	assert(d.dist_from_source(0) == 0.0);
	assert(d.dist_from_source(1) == 3.0);
	assert(d.dist_from_source(2) == 5.0);
	assert(d.dist_from_source(3) == 12.0);

	d.set_source(1);
	assert(d.dist_from_source(0) == 3.0);
	assert(d.dist_from_source(1) == 0.0);
	assert(d.dist_from_source(2) == 2.0);
	assert(d.dist_from_source(3) == 9.0);

	cout << "All Tests Passed.\n";

}

inline void
compare_algs(string graphName) {
	Graph g(graphName);
	int len = g.get_num_vertices();
	Dijkstra d(g);
	FloydWarshall f(g);

	double d1,d2,diff;

	for (int i=0; i<len; i++) {
		d.set_source(i);
		for (int j=0; j<len; j++) {
			d1 = d.dist_from_source(j);
			d2 = f.lookup(i,j);
			diff = (d1 > d2) ? d1-d2 : d2-d1;

			if (diff > THRESHOLD) {
				cout << i << "," << j <<  "\t" << diff << endl;
				assert(false);
			}
		}
	}
	cout << "Tests for Dijkstra and Floyd Warshall are equivalent\n";
}
#endif //DIJKSTRA_TEST_H