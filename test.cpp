#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#define MAX 1e9
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct NODE {
  int y, x, cost;
  bool operator<(const NODE& r) const {
    return cost > r.cost;
  }
};

int n;
int map[31][31];
int dist[31][31];

void dijkstra(int sy, int sx) {
  fill(&dist[0][0], &dist[0][0] + 31 * 31, MAX);
  priority_queue<NODE> pq;
  pq.push({sy, sx, 0});
  dist[sy][sx] = 0;

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (dist[now.y][now.x] < now.cost) continue;

    for (int i = 0; i < 4; ++i) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];
      if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
      int nextH = map[ny][nx];
      int curH = map[now.y][now.x];
      
      int adder = 0;
      if (nextH > curH) adder = (nextH - curH) * 2;
      else if (nextH == curH) adder = 1;

      int nextcost = now.cost + adder;

      if (dist[ny][nx] > nextcost) {
        dist[ny][nx] = nextcost;
        pq.push({ny, nx, nextcost});
      }
    }
  }
}

int main() {
  int t;
  cin >> t;
  for (int tc = 1; tc <= t; ++tc) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> map[i][j];
      }
    }
    dijkstra(0, 0);

    int ans = dist[n - 1][n - 1];

    cout << '#' << tc << ' ' << ans << '\n';
  }


  return 0;
}