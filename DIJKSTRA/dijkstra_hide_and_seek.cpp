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

int n, k;
int dist[100001];

void dijkstra(int start) {
  priority_queue<NODE> pq;
  fill (dist, dist + 100001, 1e9);
  pq.push({start, 0});
  dist[start] = 0;

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (dist[now.num] < now.cost) continue;

    // teleport
    int tp = now.num * 2;
    if (tp <= 100000 && dist[tp] > now.cost) {
      dist[tp] = now.cost;
      pq.push({tp, now.cost});
    }

    // -1 or +1
    for (int i = -1; i <= 1; i += 2) {
      int next = now.num + i;
      if (next < 0 || next > 100000) continue;
      int nextcost = now.cost + 1;
      if (dist[next] > nextcost) {
        dist[next] = nextcost;
        pq.push({next, nextcost});
      }
    }

  }


}

int main() {
  cin >> n >> k;
  dijkstra(n);
  cout << dist[k] << '\n';
  return 0;
}