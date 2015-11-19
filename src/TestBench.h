#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#define GRAPH_DIR "../graphs/"
#define SUBGRAPH_DIR "../graphs/subgraphs"

#include "Graph.h"
#include "FloydWarshall.h"
#include "Kruskall.h"

#include <vector>
using namespace std;

class TestBench{
public:
	TestBench(string prefix, int num_tests);
	bool	has_next(void);
	void	next(void);		/* Run the next test */
private:
	struct stats{
		double avg;
		double diff;
		stats(double a, double d): avg(a), diff(d) {}
	};
	vector<stats>	results;

	string 	prefix;
	int		num_tests;
	int 	current;	/* Test iterator */
};

inline bool
TestBench::has_next(void) {
	return (current >= num_tests);
}

#endif // TEST_BENCH_H