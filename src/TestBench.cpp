#include "TestBench.h"
#include <limits>
#include <string>
#include <iostream>
#include <cmath>

#define INFINITY std::numeric_limits<double>::max()

TestBench::TestBench(string prefix, int num_tests): 
	prefix(prefix), num_tests(num_tests), current(0),num_cmps(0) {

	global_edge_count = 0;
	global_edge_deleted = 0;
	global_count = 0;
	global_total_percent_err = 0.0;

	for (int i=0; i<BIN_COUNT; i++)
		error_bins[i] = 0;

	cout << "num_edges_before,num_edges_after,"
		<< "percent_edge_reduction,avg_soln_error,"
		<< "max_percent_error,avg_percent_error\n";
}

void
TestBench::next(void) {
	cerr << "Starting test " << current << endl;
	string filename(GRAPH_DIR + prefix + "_" + to_string(current) + ".txt");
	Graph graph(filename);


	string alt_filename(SUBGRAPH_DIR + prefix + "_" + 
		to_string(current) + ".txt");
	Graph alt_graph(alt_filename);

	current++;

	int num_vertices = graph.get_num_vertices();

	//Kruskall mst(graph);
	FloydWarshall opt(graph);
	//FloydWarshall alg(mst);
	FloydWarshall alg(alt_graph);

	double 	accum=0.0, max_error=0.0, accum_percent_slowdown=0.0;
	double	avg,avg_percent_slowdown,reduction,percent_err;
	int 	count = 0;

	/*for (int i=0; i<num_vertices; i++)
		cerr << "(0," << i << ") " << alg.lookup(0,i) << "\t" << opt.lookup(0,i) <<  endl;
	*/
	vector<double> slowdown;

	double diff, t0, t1;
	for (int i=0; i<num_vertices; i++) {
		for (int j=i; j<num_vertices; j++) {
			num_cmps++;
			global_count++;

			t1 = alg.lookup(i,j);
			t0 = opt.lookup(i,j);

			if (t0 == INFINITY) {
				cout << "Graph unsolvable\n";
				cerr << "Graph " << current << " cannot be solved\n";
				return;
			}
			if (t1 == INFINITY) {
				cout << "Reduction disconnected graph\n";
				cerr << "Graph " << current << " no longer solvable\n";
				return;
			}

			++count;
			diff = t1-t0;
			accum += diff;

			percent_err = 0;
			if (t0) {
				percent_err = diff/t0;
				accum_percent_slowdown += (diff/t0);
				max_error = (percent_err > max_error) ? percent_err: max_error;

				global_total_percent_err += percent_err;
			}
			error_bins[compute_bin(percent_err)] += 1;
		}
	}
	avg = accum/(1.0*count);
	avg_percent_slowdown = accum_percent_slowdown/(1.0*count);
	reduction = 1.0 - (alt_graph.get_num_edges()*1.0/graph.get_num_edges());

	global_edge_count += graph.get_num_edges();
	global_edge_deleted += (graph.get_num_edges() - alt_graph.get_num_edges());

	cerr << graph.get_num_edges() << "," << alt_graph.get_num_edges() << ","
		<< reduction << "," << avg << "," << max_error << "," << avg_percent_slowdown
		<< endl;

}

void
TestBench::print_results(void) {
	double freq, compression_ratio, avg_percent_err;
	compression_ratio = global_edge_deleted*1.0/global_edge_count;
	avg_percent_err = global_total_percent_err/global_count;

	cout << compression_ratio << "," << avg_percent_err << endl;

	cout << "Results..." << endl;
	for (int i=0; i<BIN_COUNT;i++)	/* Header */
		cout << BIN_GRANULARITY*i <<",";
	cout << endl;

	for (int i=0; i<BIN_COUNT;i++)	/* Number */
		cout << error_bins[i] << ",";
	cout << endl;

	for (int i=0; i<BIN_COUNT; i++) { /* Frequency*/
		freq = 1.0*error_bins[i]/num_cmps;
		cout << freq << ",";
	}
}

int
TestBench::compute_bin(double percent_err) {
	int bindex;		/* Bin index */
	percent_err *= (100/BIN_GRANULARITY);

	if (percent_err < 0.005) /* percent error < 0.025% is negligible */
		return 0;
	bindex = (int) ceil(percent_err);
	return (bindex >= BIN_COUNT) ? BIN_COUNT-1 : bindex;
}