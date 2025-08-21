#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE {
  int num, cost;
  bool operator<(const NODE & r) const {
    return cost > r.cost;
  }
};

int n, m;
vector<NODE> adj[101];
pair<int, int> dist[101];

void dijkstra(int start) {
  fill(dist, dist + 101, pair<int, int> {1e9, 101});
  priority_queue<NODE> pq;
  pq.push({start, 0});
  dist[start] = {0, 1};

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (dist[now.num].first < now.cost) continue;
    
    for (NODE next : adj[now.num]) {
      int nextcost = now.cost + next.cost;
      auto [curcost, curpassed] = dist[next.num];
      if (curcost < nextcost) continue;
      if (curcost == nextcost && curpassed <= dist[now.num].second + 1) continue;
      
      dist[next.num] = {nextcost, dist[now.num].second + 1};
      pq.push({next.num, nextcost});
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int from, to, fee, exfee, time;
    cin >> from >> to >> fee >> exfee >> time;
    int cost = (time > 10) ? fee + (time - 10) * exfee : fee;

    adj[from].push_back({to, cost});
  }

  dijkstra(1);

  if (dist[n].first >= 1e9) cout << -1 << '\n';
  else cout << dist[n].first << ' ' << dist[n].second << '\n';  
  return 0;
}