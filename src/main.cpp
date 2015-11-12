#include "Graph.h"
#include "FloydWarshall.h"
#include "Kruskall.h"
#include "../test/graph_test.h"
#include "../test/union_find_test.h"

int main() {
	//graph_test1();

	union_find_test1();
	/*
	FloydWarshall f("../graphs/test_0.txt");
	cout << f.lookup(0,0) << endl;

	Kruskall k("../graphs/test_kruskall.txt");
	k.display(); */
	return 0;
}