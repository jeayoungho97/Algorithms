#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

struct NODE {
  int num, cost;
  bool operator<(const NODE& r) const { 
    return cost > r.cost;
  }
};

bool dont[501][501];
vector<NODE> adj[501];
vector<NODE> radj[501];
int dist[501];
int n, m, start, target;

void dijkstra(int start) {
  fill(dist, dist + 501, 1e9);
  priority_queue<NODE> pq;
  pq.push({start, 0});
  dist[start] = 0;

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (dist[now.num] < now.cost) continue;

    for (NODE next : adj[now.num]) {
      if (dont[now.num][next.num]) continue;
      int nextcost = now.cost + next.cost;
      if (dist[next.num] > nextcost) {
        dist[next.num] = nextcost;
        pq.push({next.num, nextcost});
      }
    }
  }
}

int main() {
  // 다익스트라로 모든 노드에 대해서 최단 경로 찾고
  // 역추적하면서 최단경로에 있는 간선들 체크 -> dont[u].push_back(v)
  // 다시 다익스트라를 하는데 이번엔 사용불가 간선들 체크하면서 최단 경로 찾음
  // 사용불가 간선들은 현재 노드에서 사용 불가능한 다음 노드를 체크하는 방식으로.
  
  while (true) {
    // initialize
    fill(&dont[0][0], &dont[0][0] + 501 * 501, false);
    fill(adj, adj + 501, vector<NODE>{});
    fill(radj, radj + 501, vector<NODE>{});

    cin >> n >> m;
    if (n == 0 && m == 0) break;
    cin >> start >> target;
    for (int i = 0; i < m; ++i) {
      int from, to, cost;
      cin >> from >> to >> cost;

      adj[from].push_back({to, cost});
      radj[to].push_back({from, cost});
    }

    dijkstra(start);
    if (dist[target] >= 1e9) {
      cout << -1 << '\n';
      continue;
    }

    queue<NODE> q;
    q.push({target, dist[target]});
    while (!q.empty()) {
      NODE now = q.front(); q.pop();
      for (NODE next : radj[now.num]) {
        if (dont[next.num][now.num] || dist[next.num] == 1e9) continue;
        if (next.cost + dist[next.num] == now.cost) {
          q.push({next.num, dist[next.num]});
          dont[next.num][now.num] = true;
        }
      }
    }

    dijkstra(start);
    if (dist[target] >= 1e9) cout << -1 << '\n';
    else cout << dist[target] << '\n';
  }
  return 0;
}