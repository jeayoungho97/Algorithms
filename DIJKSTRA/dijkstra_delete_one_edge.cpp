#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#define MAX 1e9
using namespace std;

struct NODE {
  int num, cost;
  bool operator<(const NODE& r) const {
    return cost > r.cost;
  }
};

struct EDGE {
  int from, to, cost;
};

int n, m;
vector<NODE> adj[1001];
vector<EDGE> edge;
int distS[1001];
int distE[1001];
int ban_u, ban_v;

void dijkstra(int start, int* dist) {
  fill(dist, dist + 1001, MAX);
  priority_queue<NODE> pq;
  pq.push({start, 0});
  dist[start] = 0;

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (dist[now.num] < now.cost) continue;

    for (NODE next : adj[now.num]) {
      if ((now.num == ban_u && next.num == ban_v) || (now.num == ban_v && next.num == ban_u)) continue;
      int nextcost = now.cost + next.cost;
      if (dist[next.num] > nextcost) {
        dist[next.num] = nextcost;
        pq.push({next.num, nextcost});
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;

    adj[from].push_back({to, cost});
    adj[to].push_back({from, cost});
    edge.push_back({from, to, cost});
    edge.push_back({to, from, cost});
  }

  dijkstra(1, distS);
  dijkstra(n, distE);

  int distN[1001], ans = distS[n];
  for (EDGE e : edge) {
    if ((distS[e.from] + e.cost + distE[e.to] == distS[n]) && (distS[e.from] < distS[e.to])) {
      fill(distN, distN + 1001, MAX);
      ban_u = e.from, ban_v = e.to;
      dijkstra(1, distN);
      ans = max(ans, distN[n]);
    }
  }
  
  cout << ans << '\n';
  return 0;
}