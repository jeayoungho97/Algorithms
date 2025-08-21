#include <iostream>
#include <algorithm>
using namespace std;

struct NODE {
	int x1, x2, cost;
	bool operator<(const NODE& r) const {
		return cost < r.cost;
	}
};

int v, e;
NODE edge[100001];
int parent[10001];

int find(int x) {
	if (parent[x] == 0) return x;
	return parent[x] = find(parent[x]);
}

bool UNION(int x1, int x2) {
	x1 = find(x1);
	x2 = find(x2);
	if (x1 == x2) return 0;
	parent[x2] = x1;
	return 1;
}

int main() {
	cin >> v >> e;

	for (int i = 0; i < e; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		edge[i] = { a, b, c };
	}

	sort(edge, edge + e);

	int sum = 0, cnt = 0;
	for (int i = 0; i < e; ++i) {
		if (UNION(edge[i].x1, edge[i].x2)) {
			sum += edge[i].cost;
			cnt++;
		}
	}

	if (cnt == v - 1) cout << sum << '\n';
	else std::cout << -1 << '\n';

	return 0;
}