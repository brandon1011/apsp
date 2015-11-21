#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#define GRAPH_DIR "../graphs/"
#define SUBGRAPH_DIR "../graphs/subgraphs/"

#define BIN_COUNT	41
#define BIN_GRANULARITY 0.5

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
	void	print_results(void);
private:
	string 	prefix;
	int		num_tests;
	int 	current;	/* Test iterator */
	int		error_bins[BIN_COUNT];
	int		num_cmps;	/* Total num comparisons */

	int		compute_bin(double percent_err);
};

inline bool
TestBench::has_next(void) {
	return (current >= num_tests);
}

#endif // TEST_BENCH_H