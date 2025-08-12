// 트리 DP
// dp[n][0] => n번 노드가 얼리어답터가 아닐 때, 서브트리가 문제 조건을 만족하는 최솟값
// dp[n][1] => n번 노드가 얼리어답터일 때, 최솟값
#include <iostream>
#include <vector>
#include <array>

int n;

std::vector<std::vector<int>> adj;
std::vector<std::array<int, 2>> dp;

void dfs(int u, int p) {
  dp[u][0] = 0;
  dp[u][1] = 1;

  for (int v : adj[u]) {
    if (v == p) continue;
    dfs(v, u);
    dp[u][0] += dp[v][1];
    dp[u][1] += std::min(dp[v][0], dp[v][1]);
  }
}

int main() {
  std::cin >> n;

  adj.resize(n);
  dp.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;

    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
  }

  dfs(0, -1);

  std::cout << std::min(dp[0][0], dp[0][1]) << '\n';
  return 0;
}