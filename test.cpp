#include <iostream>
#include <queue>

struct Node {
  int y, x;
  int num;
};

std::priority_queue<Node> pq;

bool operator<(Node v, Node target) {
  return target.num < v.num;
}

int map[1100][1100];

int main() {
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> map[i][j];
      pq.push({i, j, map[i][j]});
    }
  }

  int direct[5][2] = { 0,0, -1,0, 0,1, 1,0, 0,-1};

  int cnt = 0 ;
  while (!pq.empty()) {
    Node ret = pq.top();
    pq.pop();

    if (map[ret.y][ret.x] == 0) continue;
    cnt = ret.num;
    for (int i = 0; i < 5; ++i) {
      int ny = ret.y + direct[i][0];
      int nx = ret.x + direct[i][1];

      if (ny < 0 || nx < 0 || ny >= n || nx >= n || map[ny][nx] == 0) continue;
      map[ny][nx] = 0;
    }
  }

  std::cout << cnt << "초\n";
  return 0;
}