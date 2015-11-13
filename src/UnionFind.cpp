#include "UnionFind.h"

UnionFind::UnionFind(int num) {
	for (int i=0; i<num; i++) {
		shared_ptr<Node> nd = make_shared<Node>(i);
		node_list.push_back(nd);
	}
}

int
UnionFind::set_find(int id) {
	/* Find the set of element id */
	if (id<0 || id>=node_list.size()) return -1;

	shared_ptr<Node> node = node_list.at(id);

	while(node->parent != nullptr) {
		node = node->parent;
	}

	if (node->id != id) node_list.at(id)->parent = node;	/* Path compression */

	return node->id;
}

int 
UnionFind::set_union(int a, int b) {
	/* Take union of two sets with element id's a, b */
	int rootA = this->set_find(a);
	int rootB = this->set_find(b);

	if (rootA*rootB < 0) return -1;
	if (rootA == rootB) return rootA;

	auto nodeA = node_list.at(rootA);
	auto nodeB = node_list.at(rootB);
	
	/* If nodes have equal rank, pick one arbitrarily */
	if (nodeA->rank == nodeB->rank) {
		nodeA->parent = nodeB;
		nodeB->rank++;
		return rootB;
	}

	/* Union by rank: select set with larger rank to be parent */
	if (nodeA->rank > nodeB->rank) {
		nodeB->parent = nodeA;
		return rootA;
	}
	nodeA->parent = nodeB;
	return rootB;
}