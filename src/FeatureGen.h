#ifndef FEATURE_GEN_H
#define FEATURE_GEN_H

#include "Graph.h"
#include "Dijkstra.h"

#include <string>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;

class FeatureGen {
public:
	FeatureGen(string outputFile);
	void add_graph(string pathname);
	void compute_features(void);
	void write_output(void);
private:
	void get_edge_weights(void);
	void count_edge_usage(void);
	void get_graph_properties(void);
	void get_vertex_connectivity(void);
	void get_min_adj_edge(void);

	vector<shared_ptr<Graph> >	graphs;
	string	outfile;

	/* Feature list */
	vector<int>		edge_usage;
	vector<double>	edge_weights;
	vector<int>		max_connect;	/* Node with max connectivity per edge */
	vector<int>		min_connect;	/* Node with min connectivity per edge */
	/* Graph specific properties */
	vector<int> 	num_vertices;	/* Num vertices in the graph */
	vector<int>		num_edges;		/* Num edegs in the graph */
	vector<double>	avg_weight;		/* Average weight of all edges in graph */
	vector<double>	min_adj_edge;	/* Min cost adjacent edge */

};

inline
FeatureGen::FeatureGen(string outputFile): outfile(outputFile) {}

inline void
FeatureGen::add_graph(string pathname) {
	graphs.push_back(make_shared<Graph>(pathname));
}
inline void
FeatureGen::compute_features(void) {
	get_edge_weights();
	count_edge_usage();
	get_vertex_connectivity();
	get_graph_properties();
	get_min_adj_edge();
}
#endif	// FEATURE_GEN_H