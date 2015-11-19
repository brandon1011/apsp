#include "TestBench.h"
#include <limits>
#include <string>
#include <iostream>

#define INFINITY std::numeric_limits<double>::max()

TestBench::TestBench(string prefix, int num_tests): 
	prefix(prefix), num_tests(num_tests), current(0) {}

void
TestBench::next(void) {
	cout << "Starting test " << current << endl;
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

	double 	accum = 0;
	double 	accum_percent_slowdown = 0;
	double	avg;
	double	avg_percent_slowdown;
	int 	count = 0;

	for (int i=0; i<num_vertices; i++)
		cerr << "(0," << i << ") " << alg.lookup(0,i) << "\t" << opt.lookup(0,i) <<  endl;

	vector<double> slowdown;

	double diff, t0, t1;
	for (int i=0; i<num_vertices; i++) {
		for (int j=i; j<num_vertices; j++) {
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

			if (t0) accum_percent_slowdown += (diff/t0);

		}
	}
	avg = accum/(1.0*count);
	avg_percent_slowdown = accum_percent_slowdown/(1.0*count);

	results.push_back(stats(avg, accum));
	cout << "Num Edges in original graph=" << graph.get_num_edges() << endl;
	cout << "Num_Edges in  reduced graph=" << alt_graph.get_num_edges() << endl;
	cout << "Reduction=" << alt_graph.get_num_edges()*1.0/graph.get_num_edges() << endl;
	cout << "Total difference=" << accum << endl;
	cout << "\tcount=" << count << endl;
	cout << "Average path difference=" << avg << endl;
	cout << "Average percent cost increase=" << avg_percent_slowdown << "\n\n";
}