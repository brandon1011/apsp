#include "Graph.h"
#include "FloydWarshall.h"
#include "Kruskall.h"
#include "TestBench.h"

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

	TestBench t("v100_test1", 100);

	for (int i=0; i<10; i++) {
		t.next();
	}

	dijkstra_test1();


	return 0;
}