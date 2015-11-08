#include "Vertex.h"

/* Vertex::get
 *	Return the edge id of the current edge in adj list
 *	return invalid edge if adj list is empty
 */
edge_t 
Vertex::get(void) {
	return ((it < adj.size()) ? adj.at(it) : INVALID_EDGE);
}

/* Vertex::next
 *	Increment the iterator and return the next edge id 
 */
edge_t 
Vertex::next(void) {
	it = (it+1 >= adj.size()) ? 0 : it+1;
}	

edge_t 
Vertex::add_edge(edge_t e) {
	if (e < 0) {
		return INVALID_EDGE;
	}
	adj.push_back(e);
	return e;
} 