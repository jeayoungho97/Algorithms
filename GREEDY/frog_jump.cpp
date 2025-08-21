#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

struct LOG {
  int id;
  int l, r;
  bool operator<(const LOG& right) const {
    // l 가 작은게 먼저 오도록, 같다면 r 가 작은게 먼저 오도록
    return (l == right.l) ? (r < right.r) : (l < right.l);
  }
};

int main() {
  int n, q;
  std::cin >> n >> q;

  std::vector<LOG> logs;
  logs.reserve(n);

  for (int i = 1; i <= n; ++i) {
    int x1, x2, y;
    std::cin >> x1 >> x2 >> y;
    if (x1 > x2) std::swap(x1, x2); // 왼쪽 오른쪽을 안전하게 하기 위해서
    logs.push_back({i, x1, x2});
  }

  std::sort(logs.begin(), logs.end());

  std::vector<int> parent(n + 1, -1);

  int cnt = 0;
  parent[logs[0].id] = cnt;
  int curR = logs[0].r;

  for (int i = 1; i < n; ++i) {
    const LOG& now = logs[i];
    if (now.l <= curR) {
      // 현재 통나무의 왼쪽이 이전 통나무와 겹치거나 닿음 -> 병합
      curR = std::max(curR, now.r);
      parent[now.id] = cnt;
    }
    else {
      // 새 그룹 시작
      ++cnt;
      curR = now.r;
      parent[now.id] = cnt;
    }
  }

  while (q--) {
    int a, b;
    std::cin >> a >> b;
    std::cout << (parent[a] == parent[b]) << '\n';
  }

  return 0;
}