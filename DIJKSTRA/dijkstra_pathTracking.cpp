#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct NODE {
  int num, cost;
  bool operator<(const NODE& r) const {
    return cost > r.cost;
  }
};

int n, m;
vector<NODE> adj[1001];
vector<NODE> radj[1001];
int dist[1001];

void dijkstra(int start) {
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
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;
    adj[from].push_back({to, cost});
    radj[to].push_back({from, cost});
  }

  dijkstra(1);

  vector<int> result;
  int idx = n, maxCost = 0;
  while (true) {
    result.push_back(idx);
    if (idx == 1) break;
    int curCost = dist[idx];
    for (NODE next : radj[idx]) {
      if (dist[next.num] == curCost - next.cost) {
        maxCost = max(maxCost, next.cost);
        idx = next.num;
        break;
      }
    }
  }
  sort(result.begin(), result.end());

  for (int i : result) cout << i << ' ';
  cout << '\n' << maxCost << '\n';
  return 0;
}

// 역방향으로 가면서 최소 경로를 찾아냄
// adj[n] x 중에서 dist[n] - x.cost = dist[x] 인 것을 찾아내면 됨.