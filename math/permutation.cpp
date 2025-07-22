#include <iostream>
#include <vector>

int n, m;
std::vector<int> list;

void go(int here) {
  if (list.size() == m) {
    for (int i : list) std::cout << i << ' ';
    std::cout << '\n';
    return;
  }

  for (int i = here; i <= n; ++i) {
    list.push_back(i);
    go(i + 1);
    list.pop_back();
  }
}

int main() {
  std::cin >> n >> m;

  go(1);

  return 0;
}

//BOJ 15650