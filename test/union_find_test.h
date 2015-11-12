#include "../src/UnionFind.h"

#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

#define TEST_SIZE 10


inline void
union_find_test1(void) {
	UnionFind uf(TEST_SIZE);

	for (int i=0;i<TEST_SIZE;i++) {
		assert(uf.set_find(i) == i);
	}

	int parent = uf.set_union(0,1);
	assert(uf.set_find(0) == parent && uf.set_find(1) == parent);

	for (int i=2; i<TEST_SIZE; i++) {
		assert(uf.set_find(i) != uf.set_find(0));
		assert(uf.set_find(i) != uf.set_find(1));
	}

	uf.set_union(0,2);
	assert(uf.set_find(2) == uf.set_find(1));

	for (int i=3; i<TEST_SIZE; i++) {
		assert(uf.set_find(i) != uf.set_find(0));
		assert(uf.set_find(i) != uf.set_find(1));
	}

	uf.set_union(8,9);

	for (int i=0; i<8; i++) {
		assert(uf.set_find(i) != uf.set_find(8));
		assert(uf.set_find(i) != uf.set_find(9));
	}

	uf.set_union(0,9);
	assert(uf.set_find(2) == uf.set_find(8));
	assert(uf.set_find(1) == uf.set_find(9));
	
	cout << "All tests passed.\n";
}