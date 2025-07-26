#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct _compare {
  bool operator()(int a, int b){
    if (std::abs(a) == std::abs(b)) return a > b;
    return std::abs(a) > std::abs(b);
  }
};


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::priority_queue<int, std::vector<int>, _compare> pq;
  std::vector<int> result;

  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    int input;
    std::cin >> input;

    if (input == 0) {
      if (pq.empty()) {
        result.emplace_back(0);
      }
      else {
        result.emplace_back(pq.top());
        pq.pop();
      }
    }
    else {
      pq.push(input);
    }

  }

  for (int i : result) std::cout << i << '\n';

  return 0;
}

//BOJ 11286