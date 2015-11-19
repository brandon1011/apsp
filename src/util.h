#ifndef UTIL_H
#define UTIL_H

#include "FeatureGen.h"
#include "TestBench.h"
#include "Graph.h"

#include <string>
#include <iostream>
using namespace std;

inline void
build_training_set(string prefix, int num_graphs) {
	FeatureGen fg("training_set.csv");
	std::cout << "Adding " << num_graphs << " graphs to training set.\n";
	for (int i=0; i<num_graphs; i++) {
		string graphname(prefix + "_" + to_string(i) + ".txt");
		fg.add_graph("../graphs/" + graphname);
	}
	fg.compute_features();
	std::cout << "Done computing feaures\n";
	fg.write_output();
}

inline void
build_feature_set(string prefix, int num_graphs) {
	std::cout << "Making features for " << num_graphs << " graphs.\n";
	for (int i=0; i<num_graphs; i++) {
		string graphname(prefix + "_" + to_string(i));
		FeatureGen fg(graphname + ".csv");
		fg.add_graph("../graphs/" + graphname + ".txt");
		fg.compute_features();
		fg.write_output();
	}
}

#endif // UTIL_H
