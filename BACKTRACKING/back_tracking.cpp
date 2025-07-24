#include <iostream>
#include <vector>
#include <algorithm>

int n, m;
std::vector<int> input, output;

void go(int here) {
  if (output.size() == m) {
    for (int i : output) std::cout << i << ' ';
    std::cout << '\n';
    return;
  }

  for (int i = here; i < (int)input.size(); ++i) {
    output.push_back(input[i]);
    go(i);
    output.pop_back();
  }
}

int main() {
  std::cin >> n >> m;
  input.resize(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> input[i];
  }
  std::sort(input.begin(), input.end());
  input.erase(std::unique(input.begin(), input.end()), input.end());

  go(0);

  return 0;
}

// BOJ 15666