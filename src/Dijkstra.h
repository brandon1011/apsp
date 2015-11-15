#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>

class Dijkstra : public Graph {
public:
	Dijkstra(const Graph& g);
	bool set_source(vertex_t v);
	double	dist_from_source(vertex_t u);
private:
	struct  Element {
		int 	key;
		double	val;
		Element(int k, double v): key(k), val(v) {}
	};
	static bool	cmp(Element,Element);
	void		shortest_path(void);


	vertex_t		source;		/* Source v */
	vector<double>		dist;	/* Distance btw ea v in V and source */
	vector<vertex_t>	prev;	/* Prev u in shortest path from source to v */
};

inline bool
Dijkstra::set_source(vertex_t v) {
	if (v<0 || v >= vertex_list.size()) 
		return false;
	source = v;
	shortest_path();

	return true;
}

inline double
Dijkstra::dist_from_source(vertex_t u) {
	return dist.at(u);
}

#endif //DIJKSTRA_H