#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE {
	int num, cost;
	bool operator<(const NODE& r) const {
		return cost > r.cost;
	}
};

int n, m, p, ans;
int dist[1001], rdist[1001]; // reverse dijkstra 해야함
vector<NODE> adj[1001]; // 마을은 1번부터 시작됨
vector<NODE> radj[1001]; // reverse-adj

void dijkstra(int start) {
	fill(dist, dist + 1001, 1e9);
	priority_queue<NODE> pq;
	pq.push({ start, 0 });
	dist[start] = 0;

	while (!pq.empty()) {
		NODE now = pq.top(); pq.pop();
		if (dist[now.num] < now.cost) continue;

		for (NODE next : adj[now.num]) {
			int nextcost = now.cost + next.cost;
			if (dist[next.num] <= nextcost) continue;
			dist[next.num] = nextcost;
			pq.push({ next.num, nextcost });
		}
	}
}

void reverse_dijkstra(int start) {
	fill(rdist, rdist + 1001, 1e9);
	priority_queue<NODE> pq;
	pq.push({ start, 0 });
	rdist[start] = 0;

	while (!pq.empty()) {
		NODE now = pq.top(); pq.pop();

		if (rdist[now.num] < now.cost) continue;

		for (NODE next : radj[now.num]) {
			int nextcost = now.cost + next.cost;
			if (rdist[next.num] > nextcost) {
				rdist[next.num] = nextcost;
				pq.push({ next.num, nextcost });
			}
		}
	}
}

int main() {
	cin >> n >> m >> p;
	for (int i = 0; i < m; ++i) {
		int from, to, cost;
		cin >> from >> to >> cost;
		adj[from].push_back({ to, cost });
		radj[to].push_back({ from, cost });
	}

	dijkstra(p);	// p 에서 다른 마을로 가는 것을 구함
	reverse_dijkstra(p); // 다른 마을에서 p 로 오는 것을 구함

	for (int i = 1; i <= n; ++i) {
		if (i == p) continue;
		ans = max(ans, dist[i] + rdist[i]);
	}

	cout << ans << '\n';

	return 0;
}