#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  int psum[100001];
  psum[0] = 0;
  for (int i = 1; i <= n; ++i) {
    int num;
    std::cin >> num;
    psum[i] = psum[i - 1] + num;
  }

  std::vector<int> ret;
  for (int i = 0 ; i < m; ++i) {
    int start, end;
    std::cin >> start >> end;
    ret.push_back(psum[end] - psum[start - 1]);
  }

  for (int i : ret) std::cout << i << '\n';

  return 0;
}
// BOJ 11659