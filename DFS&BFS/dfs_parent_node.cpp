#include <iostream>
#include <vector>

std::vector<int> parent;
std::vector<std::vector<int>> adj;

void dfs(int n) {
  for (const int& i : adj[n]) {
    if (parent[i]) continue;
    parent[i] = n;
    dfs(i);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  parent.resize(n + 1);
  adj.resize(n + 1);

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    std::cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1);

  for (int i = 2; i <= n; ++i) {
    std::cout << parent[i] << '\n';
  }
  return 0;
}

//BOJ 11725