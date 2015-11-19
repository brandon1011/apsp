#include "Graph.h"
#include "FloydWarshall.h"
#include "Kruskall.h"
#include "TestBench.h"
#include "FeatureGen.h"

#include "Test.h"

int main() {
	/*
	FloydWarshall f("../graphs/test_0.txt");
	cout << f.lookup(0,0) << endl;

	Kruskall k("../graphs/test_kruskall.txt");
	k.display(); */

	/*

	Graph graph("../graphs/v100_test1_0.txt");
	graph.display();

	cout << "FloydWarshall" << endl;
	FloydWarshall fw(graph);
	//fw.display();

	for (int i=0; i<fw.get_num_vertices(); i++) {
		for (int j=0; j<fw.get_num_vertices(); j++) {
			cout << i << "," << j << " d=" << fw.lookup(i,j) << endl;
		}
	} */
	/*
	TestBench t("v100_test1", 100);

	for (int i=0; i<10; i++) {
		t.next();
	}

	dijkstra_test1();
	compare_algs("../graphs/v1000_test1_0.txt");
	*/

	FeatureGen f("training.csv");
	f.add_graph("../graphs/v1000_test1_0.txt");
	f.add_graph("../graphs/v1000_test1_1.txt");
	f.add_graph("../graphs/v1000_test1_2.txt");
	f.add_graph("../graphs/v1000_test1_3.txt");
	f.add_graph("../graphs/v1000_test1_4.txt");

	f.compute_features();
	f.write_output(); 

	return 0;
}