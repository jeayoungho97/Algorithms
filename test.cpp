#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE {
	int num, cost, passed;
	bool operator<(const NODE& r) const {
		return (cost == r.cost) ? passed > r.passed : cost > r.cost;
	}
};

int n, m;
vector<NODE> adj[101];
pair<int, int> dist[101];

void dijkstra(int start) {
	priority_queue<NODE> pq;
	fill(dist, dist + 101, pair<int,int> {1e9 ,101});
	pq.push({ start, 0, 1});
	dist[start] = { 0, 1 };

	while (!pq.empty()) {
		NODE now = pq.top(); pq.pop();
		if (dist[now.num].first < now.cost) continue;
		if (dist[now.num].first == now.cost) {
			dist[now.num].second = min(dist[now.num].second, now.passed);
		}

		for (NODE next : adj[now.num]) {
			int nextcost = now.cost + next.cost;
			if (dist[next.num].first > nextcost) {
				dist[next.num].first = nextcost;
				pq.push({ next.num, nextcost, dist[now.num].second + 1});
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int from, to, fee, exfee, time;
		cin >> from >> to >> fee >> exfee >> time;

		int cost = (time > 10) ? (time - 10) * exfee + fee : fee;
		adj[from].push_back({ to, cost });
	}

	dijkstra(1);
	
	if (dist[n - 1].first >= 1e9) cout << -1 << '\n';
	else cout << dist[n - 1].first << ' ' << dist[n - 1].second << '\n';

	return 0;
}