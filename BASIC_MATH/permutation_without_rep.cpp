#include <iostream>
#include <vector>
#include <algorithm>
int n, m;
std::vector<int> input, list, visited;

void go() {
  if (list.size() == m) {
    for (int i : list) std::cout << i << ' ';
    std::cout << '\n';
    return;
  }

  for (int i = 0; i < n; ++i) {
    if (visited[i]) continue;
    list.push_back(input[i]);
    visited[i] = 1;
    go();
    visited[i] = 0;
    list.pop_back();
  }
}

int main() {
  std::cin >> n >> m;
  input.resize(n);
  visited.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> input[i];
  }
  std::sort(input.begin(), input.end());
  go();

  return 0;
}

// BOJ 15654