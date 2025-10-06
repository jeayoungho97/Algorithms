#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct NODE {
  int y, x, cost;
  bool operator<(const NODE& r) const {
    return cost > r.cost;
  }
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int N, M;
int MAP[101][101];
int dist[101][101]; // 몇 개의 벽을 부쉈는지

void dijkstra() {
  priority_queue<NODE> pq;
  pq.push({0, 0, 0});
  dist[0][0] = 0;

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();

    if (dist[now.y][now.x] < now.cost) continue;

    for (int dir = 0; dir < 4; ++dir) {
      int ny = now.y + dy[dir];
      int nx = now.x + dx[dir];

      if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;

      int nextcost = now.cost;
      if (MAP[ny][nx]) nextcost++;
      
      if (dist[ny][nx] > nextcost) {
        pq.push({ny, nx, nextcost});
        dist[ny][nx] = nextcost;
      }
    }

  }
}

int main() {
  cin >> M >> N;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      char ch;
      cin >> ch;
      MAP[i][j] = (int)(ch - '0');
    }
  }

  fill(&dist[0][0], &dist[0][0] + 101 * 101, 1e9);
  dijkstra();

  cout << dist[N - 1][M - 1] << '\n';

  return 0;
}