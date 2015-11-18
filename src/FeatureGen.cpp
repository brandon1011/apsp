#include "FeatureGen.h"

#include <fstream>
#include <iostream>

#define OUTPUT_DIR "../data/"
using namespace std;

/* Count num times each eddge appears in a 
 * 	shortest path */
void
FeatureGen::count_edge_usage(void) {
	int num_graphs = graphs.size();
	int num_vertices;

	for (int i=0; i<num_graphs; i++) {
		auto graph_ptr = graphs.at(i);
		Dijkstra d(*graph_ptr);
		num_vertices = graph_ptr->get_num_vertices();

		for (int j=0; j<num_vertices; j++) {
			d.set_source(j);
		}
		auto edge_count = d.get_edge_count();
		edge_usage.insert(edge_usage.end(), edge_count.begin(), edge_count.end());
	}
}

/* The edge weight (or cost) */
void
FeatureGen::get_edge_weights(void) {
	int num_graphs = graphs.size();
	int num_edges;

	for (int i=0; i<num_graphs; i++) {
		auto graph_ptr = graphs.at(i);
		num_edges = graph_ptr->get_num_edges();
		for (int j=0; j<num_edges; j++) {
			auto edge = graph_ptr->get_edge(j);
			edge_weights.push_back(edge->get_cost());
		}
	}
}

void 
FeatureGen::get_graph_properties(void) {
	int num_graphs = graphs.size();
	int num_edges;
	double accum, avg;

	for (int i=0; i<num_graphs; i++) {
		auto graph_ptr = graphs.at(i);
		num_edges = graph_ptr->get_num_edges();
		accum = 0;

		for (int j=0; j<num_edges; j++) {
			auto edge = graph_ptr->get_edge(j);
			accum += edge->get_cost();
		}
		avg = accum/num_edges;
		for (int j=0; j<num_edges; j++) {
			avg_weight.push_back(avg);
			this->num_edges.push_back(num_edges);
		}
	}
}

/* Vertex connectivity
 *	For each edge e = (u,v), max connectivity = Max(|Adj(u)|, |Adj(v)|)
 *	e.g the num of edges in the most connected vertex connected by edge e
 */
void
FeatureGen::get_vertex_connectivity(void) {
	int num_graphs = graphs.size();
	int num_edges;

	for (int i=0; i<num_graphs; i++) {
		auto graph_ptr = graphs.at(i);
		num_edges = graph_ptr->get_num_edges();

		for (int j=0; j<num_edges; j++) {
			auto edge = graph_ptr->get_edge(j);
			vertex_t uid = edge->get_u();
			vertex_t vid = edge->get_v();
			auto u = graph_ptr->get_vertex(uid);
			auto v = graph_ptr->get_vertex(vid);
			int adj_u = u->get_adj().size();
			int adj_v = v->get_adj().size();

			int max_adj = (adj_u > adj_v) ? adj_u : adj_v;
			int min_adj = (adj_u < adj_v) ? adj_u : adj_v;

			max_connect.push_back(max_adj);
			min_connect.push_back(min_adj);
		}
	}
}
/* For ea edge e=(u,v) in E, return min cost of edges in adj(u) U adj(v) */
void
FeatureGen::get_min_adj_edge(void) {
	int num_graphs = graphs.size();
	int num_edges;

	double min, min_u, min_v;

	for (int i=0; i<num_graphs; i++) {
		auto graph_ptr = graphs.at(i);
		num_edges = graph_ptr->get_num_edges();

		for (int j=0; j<num_edges; j++) {
			auto edge = graph_ptr->get_edge(j);
			vertex_t uid = edge->get_u();
			vertex_t vid = edge->get_v();

			min_u = graph_ptr->min_edge_v(uid);
			min_v = graph_ptr->min_edge_v(vid);
			min = (min_u < min_v) ? min_u : min_v;
			min_adj_edge.push_back(min);
		}
	}
}
void 
FeatureGen::write_output(void) {
	ofstream output(OUTPUT_DIR + outfile);
	if (!output.is_open()) {
		std::cerr << "ERROR! Cannot open output file: " << outfile << std::endl;
		return; 
	}
	for (int i=0; i<edge_usage.size();i++) {
		output << edge_usage.at(i) << "," << edge_weights.at(i)  << "," 
			<< max_connect.at(i) << "," << min_connect.at(i) << "," 
			<< min_adj_edge.at(i) << "," 
			/* Graph properties */
			<< avg_weight.at(i) << "," << num_edges.at(i) << "\n";
	}
}