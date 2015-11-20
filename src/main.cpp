#include "Graph.h"
#include "FloydWarshall.h"
#include "Kruskall.h"
#include "TestBench.h"
#include "FeatureGen.h"
#include "util.h"
#include "Test.h"

int main() {
	/* TestBench t("cmp", 1);
	t.next(); */
	//build_feature_set("v1000_test1", 100);
	compare_results("v1000_test1", 10);
	return 0;
}