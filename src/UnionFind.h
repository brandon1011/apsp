#ifndef UNION_FIND_H
#define	UNION_FIND_H

#include <memory>
#include <vector>
using namespace std;

class UnionFind {
public:
	UnionFind(int num);		/* Num of initial singletons */
	int	set_find(int id);
	int set_union(int a, int b);

private:
	struct Node {
		shared_ptr<Node>	parent;
		int	rank;
		int id;

		Node(int mid): id(mid), rank(0), parent(nullptr) {}
	};

	vector<shared_ptr<Node>	>	node_list;
};

#endif // UNION_FIND_H