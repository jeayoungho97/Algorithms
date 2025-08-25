#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<int> dq;

void deque(const std::string order) {
  if (order == "push_front") {
    int x;
    std::cin >> x;
    std::reverse(dq.begin(), dq.end());
    dq.push_back(x);
    std::reverse(dq.begin(), dq.end());
  }

  if (order == "push_back") {
    int x;
    std::cin >> x;
    dq.push_back(x);
  }

  if (order == "pop_front") {
    if (dq.empty()) std::cout << -1 << '\n';
    else {
      std::cout << dq[0] << '\n';
      std::reverse(dq.begin(), dq.end());
      dq.pop_back();
      std::reverse(dq.begin(), dq.end());
    }
  }

  if (order == "pop_back") {
    if (dq.empty()) std::cout << -1 << '\n';
    else {
      std::cout << *(dq.end() - 1) << '\n';
      dq.pop_back();
    }
  }

  if (order == "size") {
    std::cout << dq.size() << '\n';
  }

  if (order == "empty") {
    std::cout << dq.empty() << '\n';
  }

  if (order == "front") {
    if (dq.empty()) std::cout << -1 << '\n';
    else std::cout << dq[0] << '\n';
  }

  if (order == "back") {
    if (dq.empty()) std::cout << -1 << '\n';
    else std::cout << *(dq.end() - 1) << '\n';
  }
}


int main() {
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::string order;
    std::cin >> order;

    deque(order);
  }


  return 0;
}

// BOJ 10866