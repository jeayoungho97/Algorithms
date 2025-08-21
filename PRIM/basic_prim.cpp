#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct EDGE {
	int num, cost;
	bool operator<(const EDGE& r) const {
		return cost > r.cost;
	}
};

vector<vector<EDGE>> adj;

int prim(int n, vector<vector<EDGE>>& adj) {
	vector<bool> visited(n + 1, false);
	priority_queue<EDGE> pq;
	int total = 0;

	// 1번 정점에서 시작
	pq.push({ 1, 0 });

	while (!pq.empty()) {
		EDGE now = pq.top(); pq.pop();
		if (visited[now.num]) continue;
		visited[now.num] = true;
		total += now.cost;

		for (EDGE& e : adj[now.num]) {
			if (!visited[e.num]) pq.push(e);
		}
	}
	return total;
}

int main() {
	int v, e;
	cin >> v >> e;

	adj.resize(v + 1);
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	cout << prim(v, adj) << '\n';
	return 0;
}