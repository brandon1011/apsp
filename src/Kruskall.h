#ifndef KRUSKALL_H
#define KRUSKALL_H

#include "Graph.h"
#include <memory>

/* Kruskall's Alg for minimum spanning tree */
class Kruskall : public Graph {
public:
	Kruskall(const Graph& other);
	vector<shared_ptr<Edge> > getMST();
private:
	void findMST(void);
	vector<shared_ptr<Edge> > mst;	// Minimum spanning tree
};

#endif //KRUSKALL_H