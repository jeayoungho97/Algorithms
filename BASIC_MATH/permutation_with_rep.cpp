#include <iostream>
#include <vector>
#include <algorithm>

int n, m;
std::vector<int> input, output, visited;

void go() {
  if (output.size() == m) {
    for (int i : output) std::cout << i << ' ';
    std::cout << '\n';
    return;
  }

  for (int i = 0; i < n; ++i) {
    if (i > 0 && input[i] == input[i - 1] && visited[i - 1] == 0) continue;
    if (visited[i]) continue;
    output.push_back(input[i]);
    visited[i] = 1;
    go();
    visited[i] = 0;
    output.pop_back();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  input.resize(n);
  visited.resize(n, 0);
  output.reserve(m);
  for (int i = 0; i < n; ++i) {
    std::cin >> input[i];
  }

  std::sort(input.begin(), input.end());

  go();
  return 0;
}

//BOJ 15663