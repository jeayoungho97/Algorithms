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

int n, m, k;
vector<NODE> adj[1001];
priority_queue<int> dist[1001]; 

void dijkstra(int start) {
  priority_queue<NODE> pq;
  pq.push({start, 0});
  dist[start].push(0);

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();

    for (NODE next : adj[now.num]) {
      int nextcost = next.cost + now.cost;
      if (dist[next.num].size() < k) {
        dist[next.num].push(nextcost);
      }
      else if (dist[next.num].top() > nextcost){
        dist[next.num].pop();
        dist[next.num].push(nextcost);
      }
      else continue;

      pq.push({next.num, nextcost});
    }
  }
}

int main() {
  cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;
    adj[from].push_back({to, cost});
  }

  dijkstra(1);

  for (int i = 1; i <= n; ++i) {
    if (dist[i].size() != k) cout << -1 << '\n';
    else cout << dist[i].top() << '\n';
  }

  return 0;
}