// 두 로봇
// 그냥 DFS 로 이어서
// 가면서 있었던 경로 중에서 가장 긴 놈을 빼면 답임

#include <iostream>
#include <algorithm>
#include <vector>

struct node {
  std::vector<std::pair<int,int>> next; // next node number, distance
};

int n, a, b, sum, longest, ans;
bool found;
std::vector<node> adj;
std::vector<bool> visited;

void go(int here) {
    if (found) return;

    if (here == b) {
      found = true;
      ans = sum - longest;
      return;
    }

    const auto &next_nodes = adj[here].next;
    for (int i = 0; i < next_nodes.size(); ++i) {
      const int next_node = next_nodes[i].first;
      const int distance = next_nodes[i].second;

      if (!visited[next_node]) {
        sum += distance;
        int prev = longest;
        longest = std::max(longest, distance);
        visited[next_node] = 1;
        go(next_node);
        visited[next_node] = 0;
        longest = prev;
        sum -= distance;
      }
    }
}

int main() {
    std::cin >> n >> a >> b;

    adj.resize(n + 1);
    visited.resize(n + 1, false);

    for (int i = 0; i < n - 1; ++i) {
        int x, y, l;

        std::cin >> x >> y >> l;
        adj[x].next.push_back({y, l});
        adj[y].next.push_back({x, l});
    }

    visited[a] = 1;
    go(a);

    std::cout << ans << '\n';

    return 0;
}