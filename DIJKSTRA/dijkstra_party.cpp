#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct NODE {
  int num, cost;
  bool operator<(const NODE& r) const {
    return cost > r.cost;
  }
};

vector<NODE> adj[1001];
int dist[1001];
int distX[1001];
int n, m, x, ans;

void dijkstra(int start, int* dist) {
  fill(dist, dist + 1001, 1e9);
  priority_queue<NODE> pq;
  pq.push({start, 0});
  dist[start] = 0;

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (dist[now.num] < now.cost) continue;

    for (NODE next : adj[now.num]) {
      int nextcost = now.cost + next.cost;
      if (dist[next.num] > nextcost) {
        dist[next.num] = nextcost;
        pq.push({next.num, nextcost});
      }
    }
  }

  ans = max(ans, dist[x] + distX[start]);
}

int main() {
  cin >> n >> m >> x;
  for (int i = 0; i < m; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;

    adj[from].push_back({to, cost});
  }
  dijkstra(x, distX);

  for (int i = 1; i <= n; ++i) {
    dijkstra(i, dist);
  }

  cout << ans << '\n';
	return 0;
}