#include <iostream>
#include <vector>

std::vector<int> visited;
std::vector<std::vector<int>> linked;

void dfs(int here) {
  for (int there : linked[here]) {
    if (visited[there]) continue;
    visited[there] = 1;
    dfs(there);
  }
}

int main() {
  int n;
  std::cin >> n;
  visited.resize(n + 1, 0);
  linked.resize(n + 1);

  int connected;
  std::cin >> connected;
  for (int i = 0; i < connected; ++i) {
    int cpA, cpB;
    std::cin >> cpA >> cpB;

    linked[cpA].push_back(cpB);
    linked[cpB].push_back(cpA);
  }

  visited[1] = 1;
  dfs(1);
  
  int result = 0;
  for (int i = 2; i <= n; ++i) {
    if (visited[i] == 1) {
      result++;
    }
  }

  std::cout << result << '\n';
  return 0;
}

// BOJ 2606