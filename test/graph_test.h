#include "../src/Graph.h"
#include "../src/Vertex.h"
#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

inline void
graph_test1(void) {
	Graph g(3);
	g.add_edge(0,1,10);

	shared_ptr<Vertex> v1 = g.get_vertex(0);
	shared_ptr<Vertex> v2 = g.get_vertex(1);

	assert(v1 != nullptr && v2 != nullptr);
 	
 	/* Vertex id's */
	assert(v1->get_id() == 0);
	assert(v2->get_id() == 1);
	/* Num of edges in adj list */
	assert(v1->length() == 1);
	assert(v2->length() == 1);

	auto v2p = g.adj_get_vertex(0);
	assert(v2p == v2);

	assert(g.adj_get_edge(0)->adj(0) == 1); /* Get first edge in adj(0) and find v */
	assert(g.adj_get_edge(0)->adj(1) == 0); 
	assert(g.adj_get_edge(1)->adj(1) == 0); 
	assert(g.adj_get_edge(1)->adj(0) == 1); 

	auto e1 = g.adj_get_edge(0);
	auto e1p = g.adj_get_edge(1);
	assert(e1 == e1p); 	/* v1, v2 have same edge*/

	assert(g.adj_next(0) == e1);	/* Should only be single edge in graph */

	/* Add 2nd edge*/
	auto e2 = g.add_edge(0,2,10);
	auto v3 = g.get_vertex(2);

	assert(v3 != nullptr);
	assert(v1->length() == 2);
	assert(v2->length() == 1);
	assert(v3->length() == 1);

	assert(g.adj_get_edge(0) == e1);
	auto e2p = g.adj_get_edge(2); /* First edge in v3 */

	assert(e2p != e1);
	assert(g.adj_next(0) == e2p); /* Increment v1's adj list */
	assert(g.adj_next(0) == e1); /* Increment again (wrap around) */

	cout << "All Tests Passed\n"; 
}